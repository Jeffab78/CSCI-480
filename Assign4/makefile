
CCFLAGS = -ansi -Wall -std=c++11 -Wextra

hw4.exe: hw4.o Street.o
	g++ $(CCFLAGS) -o hw4.exe hw4.o Street.o

hw4.o: hw4.cpp Street.h
	g++ $(CCFLAGS) -c hw4.cpp

Street.o: Street.cpp Street.h
	g++ $(CCFLAGS) -c Street.cpp

clean:
	-rm *.o hw4.exe
