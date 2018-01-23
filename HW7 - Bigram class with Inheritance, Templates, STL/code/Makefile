all: exe

exe: _mainTester.o 
	g++ -std=c++11 _mainTester.o  -o exe

_mainTester.o: _mainTester.cpp
	g++ -c -std=c++11 _mainTester.cpp


clean:
	rm *.o exe
