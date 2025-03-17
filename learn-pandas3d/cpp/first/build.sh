clang++ -arch x86_64 -c first.cpp -o first.o -std=gnu++11 -I/Library/Developer/Panda3D/include
clang++  -arch x86_64 first.o -o first -L/Library/Developer/Panda3D/lib -lp3framework -lpanda -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3direct
