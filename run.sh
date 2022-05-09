make clean 
make all

# echo starting
./main $1 out3.txt
minisat out3.txt model.txt > t2.tmp
./find_model
# ./zchaff out.txt