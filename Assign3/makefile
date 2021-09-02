CCFLAGS = -ansi -Wall  -std=c++11 -Wextra

hw3.exe: hw3.o flightInfo.o
	g++ $(CCFLAGS) -o hw3.exe hw3.o flightInfo.o

hw3.o: hw3.cpp
	g++ $(CCFLAGS) -c hw3.cpp

flightInfo.o: flightInfo.cpp flightInfo.h
	g++ $(CCFLAGS) -c flightInfo.cpp

clean:
	-rm *.o hw3.exe
