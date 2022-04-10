all: main


CC=clang

CFLAGS= -g -Wall -Wextra -Werror -Wno-unused-parameter

main: main.o types.o constraints.o


clean:
	rm -f main *.o