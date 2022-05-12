CC = clang

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m # No Color

FILES = main satTo3Sat

all: $(FILES)

main: sat.o dimacs.o

satTo3Sat: satTo3Sat.o sat.o dimacs.o

################
# Tests       #
################

TESTS_CONV = ../Tests/Simple/*/*

TESTS_SAT = ../Tests/Sat/uf20/* ../Tests/Sat/uf50/* ../Tests/Sat/uf75/* ../Tests/Sat/uf100/*
TESTS_UNSAT = ../Tests/Unsat/uuf50/* ../Tests/Unsat/uuf75/*

tests_sat: main
	@rm -f time.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_SAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s; \
	done

tests_unsat: main
	@rm -f time.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_UNSAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i u; \
	done

test_all: tests_sat tests_unsat

test_conversion: satTo3Sat
	@for i in $(TESTS_CONV) ; do \
		printf "$(GREEN)`basename $$i .cnf`$(NC)\n" ; \
		./satTo3Sat $$i ../Tests/3Sat/`basename $$i .cnf`_3sat.cnf; \
	done

clean:
	rm -f *.o $(FILES) temp.cnf
