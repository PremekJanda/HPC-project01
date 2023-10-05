#!/bin/bash -l

DIR=1

if [ "$#" -ne 1 ]
then
    DIR=1
    while [ -d "$DIR" ]
    do
        DIR=$[$DIR+1]
    done
else
    DIR=$i
fi

echo "Creating new directory $DIR"
mkdir $DIR

make
./run_matrixmult.sh > "out.txt"

cat "out.txt" | grep -i -E  "Average|blocked" | sed 'N;s/\n#/\ /g' > "out.data"

cp out.txt out.data $DIR

gnuplot performance_comparison.gp

