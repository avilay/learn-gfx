clang++ -c fourth.cpp -o fourth.o -std=gnu++11 -I/Library/Developer/Panda3D/include
clang++ fourth.o -o fourth -L/Library/Developer/Panda3D/lib -lp3framework -lpanda -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3direct
