T=Simple/UNSAT/* 
for i in $T
do
    # mv $i Simple/UNSAT/`basename $i .txt`
    mv $i $i.cnf
done