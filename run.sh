make clean 
make all
time ./main $1 "${1%/*}/"`basename $1 .in`.cnf
minisat "${1%/*}/"`basename $1 .in`.cnf "${1%/*}/"`basename $1 .in`.model
./find_model "${1%/*}/"`basename $1 .in`.model
