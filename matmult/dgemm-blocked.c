/* 
    Please include compiler name below (you may also include any other modules you would like to be loaded)

COMPILER= gnu

    Please include All compiler flags and libraries as you want them run. You can simply copy this over from the Makefile's first few lines
 
CC = cc
OPT = -O3
CFLAGS = -Wall -std=gnu99 $(OPT)
MKLROOT = /opt/intel/composer_xe_2013.1.117/mkl
LDLIBS = -lrt -Wl,--start-group $(MKLROOT)/lib/intel64/libmkl_intel_lp64.a $(MKLROOT)/lib/intel64/libmkl_sequential.a $(MKLROOT)/lib/intel64/libmkl_core.a -Wl,--end-group -lpthread -lm

*/

#define min(__a, __b) ((__a) < (__b) ? (__a) : (__b))

const char* dgemm_desc = "Naive, three-loop dgemm.";

extern int block_size;

/* This routine performs a dgemm operation
 *  C := C + A * B
 * where A, B, and C are lda-by-lda matrices stored in column-major format.
 * On exit, A and B maintain their input values. */    
void square_dgemm (int n, double* A, double* B, double* C)
{
  // First method
  // int block_size = 10;
  int i, j, k, i_b, j_b, k_b;
  double tmp;

  // partitioning
  for (i_b = 0; i_b < n; i_b += block_size) {
    for (j_b = 0; j_b < n; j_b += block_size) {
      for (k_b = 0; k_b < n; k_b += block_size) {
        // conduct naive matrix multiplication
        // min is used to prevent overflow
        for (i = i_b; i < min(i_b+block_size, n); i++) {
          for (j = j_b; j < min(j_b+block_size, n); j++) {
            // load C[i][j]
            tmp = C[i+j*n];
            for (k = k_b; k < min(k_b+block_size, n); k++) {
              tmp += A[i+k*n] * B[k+j*n];
            }
            // store C[i][j]
            C[i+j*n] = tmp;
          }
        }
      }
    }
  }


  // // Second method
  // int block_size = 32;
  // int i, j, k, j_b, k_b;
  // double tmp;

  // for (k_b = 0; k_b < n; k_b += block_size) {
  //   for (j_b = 0; j_b < n; j_b += block_size) {
  //     for (i = 0; i < n; i++) {
  //       for (k = k_b; k < min(k_b + block_size, n); k++) {
  //         tmp = A[i+k*n];
  //         for (j = j_b; j < min(j_b + block_size, n); j++) {
  //             C[i+j*n] += tmp * B[k+j*n];
  //         }
  //       }
  //     }
  //   }
  // }



  // // Third method
  // int block_size = 16;
  // int i, j, k, i_b, j_b, k_b;

  // for (i_b = 0; i_b < n; i_b += block_size) {
  //   for (j_b = 0; j_b < n; j_b += block_size) {
  //     for (k_b = 0; k_b < n; k_b += block_size) {
  //       for (i = i_b; i < min(i_b+block_size, n); i++) {
  //         for (j = j_b; j < min(j_b+block_size, n); j++) {
  //           for (k = k_b; k < min(k_b+block_size, n); k++) {
  //             C[i+j*n] += A[i+k*n] * B[k+j*n];
  //           }
  //         }
  //       }
  //     }
  //   }
  // }

}
