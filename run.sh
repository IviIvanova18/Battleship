make clean 
make
./main $1 out1.txt
minisat out1.txt model.txt
# clang find_model.c
./a.out 
# ./zchaff out.txt