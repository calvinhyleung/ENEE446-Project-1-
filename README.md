# Tomasulo-Algorithm-Simulator

This project is to simulate the workings of Tomasulo Algorithm for a RISCV machine. Tomasulo Algorithm is a pipelining technique 
in processors that uses functional units to provide a more efficient computing speed compare to serial. More information about the 
alsorithm can be found here, https://en.wikipedia.org/wiki/Tomasulo_algorithm

The simulator would first treat the provided program written with the RISCV instruction set as a program saved in a physical memory. 
Through each cycle, the simulator would act like a pipeline to fetch, decode, excute and writeback to the machine. Each cycle is caredully 
calculated depending on the instructions. Hazards such as structural hazard, data hazard, branching hazard are all accounted into the 
simulation, thus impacting the clock cycles. 

Steps to run the simulation: 
1. Use Linux or WSL
2. Run `make` 
3. Run `./pipesim -b ` "instruction file" ` -o io_pipe.fu`
4. Sample Command `./pipesim -b newton -o io_pipe.fu`
5. Instruction file included: 
	- simple 
	- newton 
	- cos
	- vect
	- *instruction file are RISCV commands
