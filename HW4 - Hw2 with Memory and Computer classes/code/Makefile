all: exe

exe: main.o CPU.o CPUProgram.o Memory.o Computer.o
	g++ main.o CPU.o CPUProgram.o Memory.o Computer.o -o exe

main.o: main.cpp
	g++ -c main.cpp

CPU.o: CPU.cpp
	g++ -c CPU.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c CPUProgram.cpp

Memory.o: Memory.cpp
	g++ -c Memory.cpp

Computer.o: Computer.cpp
	g++ -c Computer.cpp

clean:
	rm *.o exe
