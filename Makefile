start: Show.o PIF.o Main.o; g++ -ostart Show.o PIF.o Main.o
Show.o:  Show.cpp; g++ -c Show.cpp
PIF.o:  PIF.cpp; g++ -c PIF.cpp
Main.o:  Main.cpp Show.h PIF.h; g++ -c Main.cpp
test.o:	test.cpp PIF.h; g++ -c test.cpp 
test:	test.o PIF.o; g++ -otest test.o PIF.o /home/dima/pr2/Unity/src/unity.c
runtests:	test; ./test
clean: rm --force Show.o PIF.o Main.o test.o start test
