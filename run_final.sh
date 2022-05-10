make clean 
make all
./main $1 "${1%/*}/"`basename $1 .in`.cnf
minisat "${1%/*}/"`basename $1 .in`.cnf "${1%/*}/"`basename $1 .in`.model > t2.tmp
./find_model_final "${1%/*}/"`basename $1 .in`.model $1 > "${1%/*}/"`basename $1 .in`.solution
python3 Graphics/graphics.py $1 "${1%/*}/"`basename $1 .in`.solution

