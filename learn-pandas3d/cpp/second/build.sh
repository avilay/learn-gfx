clang++ -c second.cpp -o second.o -std=gnu++11 -I/Library/Developer/Panda3D/include
clang++ second.o -o second -L/Library/Developer/Panda3D/lib -lp3framework -lpanda -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3direct
