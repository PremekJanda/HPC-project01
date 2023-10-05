#!/bin/bash -l

#SBATCH --job-name=matrixmult
#SBATCH --time=00:30:00
#SBATCH --nodes=1
#SBATCH --output=matrixmult-%j.out
#SBATCH --error=matrixmult-%j.err

# load modules
if command -v module 1>/dev/null 2>&1; then
   module load gcc/10.1.0 intel-mkl/2020.1.217-gcc-10.1.0-qsctnr6 gnuplot
fi

export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1

# echo "==== benchmark-naive ======================"
# ./benchmark-naive 32 | tee timing_basic_dgemm.data
# echo
# echo "==== benchmark-blas ======================="
# ./benchmark-blas 32 | tee timing_blas_dgemm.data
# echo
# echo "==== benchmark-blocked ===================="
# ./benchmark-blocked 32 | tee timing_blocked_dgemm.data
# echo
# echo "==== plot results ========================="
# gnuplot -e "filename='timing.ps'" "timing.gp"

for i in {2..32}
do
   echo "blocked testing $i"
   ./benchmark-blocked $i | tee "timing_blocked_dgemm.data"
   gnuplot -e "filename='timing_$i.ps'" "timing.gp"
done;

for i in {32..64..2}
do
   echo "blocked testing $i"
   ./benchmark-blocked $i | tee "timing_blocked_dgemm.data"
   gnuplot -e "filename='timing_$i.ps'" "timing.gp"
done;

for i in {64..128..4}
do
   echo "blocked testing $i"
   ./benchmark-blocked $i | tee "timing_blocked_dgemm.data"
   gnuplot -e "filename='timing_$i.ps'" "timing.gp"
done;
