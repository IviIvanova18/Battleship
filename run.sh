make clean 
make
./main Graphics/Tests/game1.txt out.txt
minisat out.txt model.txt
clang find_model.c
./a.out 
# ./zchaff out.txt