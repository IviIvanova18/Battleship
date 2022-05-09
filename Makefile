ALL = main find_model

all: $(ALL)


# CC=gcc -O
CC=clang

# CFLAGS= -g -Wall -Wextra -Werror -Wno-unused-parameter

main: main.o types.o constraints.o

find_model: find_model.o types.o constraints.o

clean:
	rm -f $(ALL) *.o