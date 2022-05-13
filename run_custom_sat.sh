make all
./main $1 "${1%/*}/"`basename $1 .in`.cnf
cd Solvers/K-Sat/
make 
./main  "../../${1%/*}/"`basename $1 .in`.cnf s 3 "../../${1%/*}/"`basename $1 .in`.model
cd ../..
./find_model "${1%/*}/"`basename $1 .in`.model $1
# python3 Graphics/graphics.py $1 "${1%/*}/"`basename $1 .in`.solution