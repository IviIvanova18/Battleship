make clean 
make all
./main $1 "${1%/*}/"`basename $1 .in`.cnf
minisat "${1%/*}/"`basename $1 .in`.cnf "${1%/*}/"`basename $1 .in`.model
./find_model "${1%/*}/"`basename $1 .in`.model

# echo "${1%/*}/"`basename $1 .in`.cnf
