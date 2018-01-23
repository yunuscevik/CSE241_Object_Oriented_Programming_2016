all: exe

exe: main.o CPU.o CPUProgram.o
	g++ main.o CPU.o CPUProgram.o -o exe

main.o: main.cpp
	g++ -c main.cpp

CPU.o: CPU.cpp
	g++ -c CPU.cpp
	
CPUProgram.o: CPUProgram.cpp
	g++ -c CPUProgram.cpp
clean:
	rm *.o exe
