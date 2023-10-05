# On Euler, we will benchmark your DGEMM's performance against the performance
# of the default vendor-tuned DGEMM. This is done in benchmark-blas.
#

CC = gcc
OPT = -O2
# ! UNCOMMENT in case of printing stuff
# OPT = -O2 -D PRINT
CFLAGS = -Wall -std=gnu99 $(OPT)
LDFLAGS = -Wall
# librt is needed for clock_gettime
LDLIBS = -lrt -Wl,--no-as-needed -L${MKLROOT}/lib/intel64 -lmkl_intel_lp64 -lmkl_core -lmkl_sequential -lpthread -lm -ldl -m64 -I${MKLROOT}/include

targets = benchmark-naive benchmark-blocked benchmark-blas test-naive test-blocked
objects = benchmark.o dgemm-naive.o dgemm-blocked.o dgemm-blas.o test-naive.o test-blocked.o

.PHONY : default, all, clean, run_test
default : all

all : clean $(targets)

benchmark-naive : benchmark.o dgemm-naive.o 
	$(CC) -o $@ $^ $(LDLIBS)
benchmark-blocked : benchmark.o dgemm-blocked.o
	$(CC) -o $@ $^ $(LDLIBS)
benchmark-blas : benchmark.o dgemm-blas.o
	$(CC) -o $@ $^ $(LDLIBS)
test-naive : test.o dgemm-naive.o 
	$(CC) -o $@ $^ $(LDLIBS)
test-blocked : test.o dgemm-blocked.o 
	$(CC) -o $@ $^ $(LDLIBS)

%.o : %.c
	$(CC) -c $(CFLAGS) $<

test.o : test.c
	$(CC) -c $(CFLAGS) -D PRINT $<

clean:
	rm -f $(targets) $(objects)

run_test:
	./run_test
	
	
