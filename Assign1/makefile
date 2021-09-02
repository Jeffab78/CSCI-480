
CCFLAGS = -ansi -Wall -std=c++11 -Wextra

hw1.exe: hw1.o procInfo.o
	g++ $(CCFLAGS) -o hw1.exe hw1.o procInfo.o

hw1.o: hw1.cpp procInfo.h
	g++ $(CCFLAGS) -c hw1.cpp

procInfo.o: procInfo.cpp procInfo.h
	g++ $(CCFLAGS) -c procInfo.cpp

clean:
	-rm *.o hw1.exe
