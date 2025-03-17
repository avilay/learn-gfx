# Build Commands

```shell
clang++ -c first.cpp -o first.o -std=gnu++11 -I/Library/Developer/Panda3D/include
clang++ first.o -o first -L/Library/Developer/Panda3D/lib -lp3framework -lpanda -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3direct
```

When trying to run `./first` I'll see the following error -

```
dyld: Library not loaded: @loader_path/../lib/libp3framework.1.10.dylib
  Referenced from: /Users/avilay/projects/bitbucket/learn/learn-pandas3d/cpp/./first
  Reason: image not found
[1]    82114 abort      ./first
```

The reason is that Panda3D framework libraries are linked with their relative path instead of the full absolute path. If I examine the linked libraries using `otool` I'll see this -

```
otool -L first
first:
	@loader_path/../lib/libp3framework.1.10.dylib (compatibility version 1.10.0, current version 1.10.6)
	@loader_path/../lib/libpanda.1.10.dylib (compatibility version 1.10.0, current version 1.10.6)
	@loader_path/../lib/libpandaexpress.1.10.dylib (compatibility version 1.10.0, current version 1.10.6)
	@loader_path/../lib/libp3dtoolconfig.1.10.dylib (compatibility version 1.10.0, current version 1.10.6)
	@loader_path/../lib/libp3dtool.1.10.dylib (compatibility version 1.10.0, current version 1.10.6)
	@loader_path/../lib/libp3direct.1.10.dylib (compatibility version 1.10.0, current version 1.10.6)
	/usr/lib/libc++.1.dylib (compatibility version 1.0.0, current version 902.1.0)
	/usr/lib/libSystem.B.dylib (compatibility version 1.0.0, current version 1281.100.1)
```

As can be seen the Mac OS dynamic linker will use `@loader_path` to find the framework libs. And this macro resolves to the directory that the executable is in. Importantly it is not the current working directory from where the executable is invoked, but the directory in which the executable, in this case, `first` lives.

There are four ways to solve this problem:

  1. Set the `DYLD_LIBRARY_PATH` environment variable.
  2. Copy `first` to some directory inside `/Library/Developer/Panda3D/<anydir>
  3. Copy the framework libraries to where the executable lives
  4. Use the `install_name_tool` to change the paths inside the Mach-O executable

### 1. Setting Environment Variable
This is the simplest way to solve this issue. Simply run -

```shell
DYLD_LIBRARY_PATH=/Library/Developer/Panda3D/lib ./first
```

For convenience this can be wrapped inside a shell script.

### 2. Copy Mach-O to Panda3D
This is a very bad hack where I copy `first` to any directory s.t the framework libraries exist in `../lib`.

```shell
cp first /Library/Developer/Panda3D/samples
```

Then execut it as usual -

```shell
/Library/Developer/Panda3D/samples/first
```

### 3. Copy Panda3D Framework to Mach-O
This is reverse of the above method, where I copy the relevant libraries to where the executable lives. Just as bad.

### 4. Change Linked Paths
This is slightly better than moving files around. `install_name_tool` is a pretty cool tool where I can muck around with the linked paths inside a Mach-O executable. I can just change all the `@loader_path` paths to their absolute path. To show this first I'll copy `first` to `second`.

```shell
cp first second
install_name_tool -change @loader_path/../lib/libp3framework.1.10.dylib /Library/Developer/Panda3D/lib/libp3framework.1.10.dylib second
install_name_tool -change @loader_path/../lib/libpanda.1.10.dylib /Library/Developer/Panda3D/lib/libpanda.1.10.dylib second
install_name_tool -change @loader_path/../lib/libpandaexpress.1.10.dylib /Library/Developer/Panda3D/lib/libpandaexpress.1.10.dylib second
install_name_tool -change @loader_path/../lib/libp3dtoolconfig.1.10.dylib /Library/Developer/Panda3D/lib/libp3dtoolconfig.1.10.dylib second
install_name_tool -change @loader_path/../lib/libp3dtool.1.10.dylib /Library/Developer/Panda3D/lib/libp3dtool.1.10.dylib second
install_name_tool -change @loader_path/../lib/libp3direct.1.10.dylib /Library/Developer/Panda3D/lib/libp3direct.1.10.dylib second
```

I am sure there is an easier way to do this, but for now this works.
