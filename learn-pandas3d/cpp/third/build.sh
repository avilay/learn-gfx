clang++ -c third.cpp -o third.o -std=gnu++11 -I/Library/Developer/Panda3D/include
clang++ third.o -o third -L/Library/Developer/Panda3D/lib -lp3framework -lpanda -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3direct
