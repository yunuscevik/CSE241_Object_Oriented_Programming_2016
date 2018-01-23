all: exe

exe: _mainTester.o CPU.o CPUProgram.o CPUProgramDyn.o Memory.o Computer.o
	g++ _mainTester.o CPU.o CPUProgram.o CPUProgramDyn.o Memory.o Computer.o -o exe

_mainTester.o: _mainTester.cpp
	g++ -c _mainTester.cpp

CPU.o: CPU.cpp
	g++ -c CPU.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c CPUProgram.cpp

CPUProgramDyn.o: CPUProgramDyn.cpp
	g++ -c CPUProgramDyn.cpp

Memory.o: Memory.cpp
	g++ -c Memory.cpp

Computer.o: Computer.cpp
	g++ -c Computer.cpp

clean:
	rm *.o exe
