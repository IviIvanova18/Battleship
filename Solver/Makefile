RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[1;33m
NC = \033[0m # No Color

TESTS_SAT = Tests/Sat/uf20/* #Tests/Sat/uuf50/*
TESTS_UNSAT = Tests/Unsat/pigon/*
main: sat.o dimacs.c modal.c solver1.c solver2.c solver3.c

time: time.o

tests_sat3: main
	@rm -f Tests/solver3.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_SAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s 3 Tests/solver3.time; \
	done

tests_sat2: main
	@rm -f Tests/solver2.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_SAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s 2 Tests/solver2.time; \
	done

tests_sat1: main
	@rm -f Tests/solver1.time
	@printf "$(YELLOW)##### Running SAT Tests ##### $(NC) \n"
	@for i in $(TESTS_SAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s 1 Tests/solver1.time; \
	done

tests_simpsat: main
	@printf "$(YELLOW)##### Running Simple UNSAT Tests ##### $(NC) \n"
	@for i in Tests/Simple/SAT/* ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i s 3 ; \
	done

tests_unsat: main
	@printf "$(YELLOW)##### Running UNSAT Tests ##### $(NC) \n"
	@for i in $(TESTS_UNSAT) ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i u 3 Tests/solver3.time; \
	done

tests_simpunsat: main
	@printf "$(YELLOW)##### Running Simple UNSAT Tests ##### $(NC) \n"
	@for i in Tests/Simple/UNSAT/* ; do \
		printf "$(GREEN)`basename $$i .txt`$(NC): " ; \
		./main $$i u 3 ; \
	done

clean:
	rm -f *.o main time