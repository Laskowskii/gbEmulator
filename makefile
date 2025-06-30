files := ./src/main.c ./src/cpu.c ./src/rom.c ./src/memory.c

hello:
	gcc ${files} -o gbemu