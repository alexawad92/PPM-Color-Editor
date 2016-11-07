PPM:	colorChanger.o PPM.o
	g++ *.o -o colorChanger
colorChanger.cpp:	colorChanger.cpp PPM.h
	g++  -c colorChanger.cpp
PPM.cpp:	PPM.cpp PPM.h
	g++ -Wall -c PPM.cpp
