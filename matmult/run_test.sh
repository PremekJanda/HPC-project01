#!/bin/bash -l

# $1 : size of matrix N (width and height)
# $2 : type of filling
#      - random (gaussian [-1,1])
#      - inc_dec_ones (A - increasing order, B - decreasing order, C - all ones)

echo "Compilation..."
make -s clean && make -s

echo "Test run"
./test-blocked $1 $2 > out-blocked.txt
./test-naive $1 $2 > out-naive.txt

diff out-naive.txt out-blocked.txt >/dev/null

if [ $? -eq 1 ]
then
   echo "Error: different files"
else
   echo "Ok: Comparison ok"
fi
