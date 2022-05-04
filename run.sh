make clean 
make
./main Graphics/Tests/game1.txt out.txt
minisat out.txt model.txt
# ./zchaff out.txt