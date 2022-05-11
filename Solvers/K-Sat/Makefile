CC=clang

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m # No Color

#TESTS_SAT = ../Tests/Sat/uf20/*
# TESTS_SAT = ../Tests/Sat/uf50/*

TESTS_UNSAT = ../Tests/Unsat/uuf50/*
SIMPLE_SAT = ../Tests/Simple/SAT/*
SIMPLE_UNSAT = ../Tests/Simple/UNSAT/*

SOLVERS = 1 2 3

main: sat.o dimacs.c modal.c solver1.c solver2.c solver3.c

tests_sat3: main
	@rm -f ../Tests/solver3.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_SAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s 3 ../Tests/solver3.time; \
	done

tests_unsat3: main
	@rm -f Tests/solver3.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_UNSAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i u 3 ../Tests/solver3.time; \
	done

test3: tests_sat3 tests_unsat3

tests_sat2: main
	@rm -f Tests/solver2.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(SIMPLE_SAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s 2 ../Tests/solver2.time; \
	done

tests_sat1: main
	@rm -f Tests/solver1.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_SAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s 1 ../Tests/solver1.time; \
	done

tests_simpsat: main
	@printf "$(YELLOW)##### Running Simple SAT Tests ##### $(NC) \n"
	@for i in $(SOLVERS) ; do \
  		printf "$(YELLOW)##### Solver $$i ##### $(NC) \n" ; \
		for j in $(SIMPLE_SAT) ; do \
			printf "$(GREEN)`basename $$j .txt`$(NC): " ; \
			./main $$j s $$i ; \
		done ; \
  	done

tests_simpunsat: main
	@printf "$(YELLOW)##### Running Simple UNSAT Tests ##### $(NC) \n"
	@for i in $(SOLVERS) ; do \
  		printf "$(YELLOW)##### Solver $$i ##### $(NC) \n" ; \
		for j in $(SIMPLE_UNSAT) ; do \
			printf "$(GREEN)`basename $$j .txt`$(NC): " ; \
			./main $$j u $$i ; \
		done ; \
  	done

test_simple: tests_simpsat tests_simpunsat

clean:
	rm -f *.o main time