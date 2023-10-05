#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

extern void square_dgemm(int, double*, double*, double*);

#define MAX_BOLOCK_SIZE 32

int block_size = 10;

#define var(__v) #__v
#define abs(__a) (__a < 0 ? -__a : __a)

double array_max(double *M, int n) {
  double max = abs(M[0]);
  
  for (int i = 1; i < n; i++)
    if (abs(M[i]) > max)
      max = abs(M[i]);

  return max;
}


void print_matrix(int n, double *M, char *matrix_name) {
  printf("\nMatrix: %s\n", matrix_name);
  char number_buffer[50];
  double max_value = array_max(M, n*n);
  int print_len = max_value > 1e6 || max_value < 10 ? 13 : (int)log10(max_value)+1;

  for (int i = 0; i < n*n; i += n) {
    for (int j = 0; j < n; j++) {
      sprintf(number_buffer, "%g", M[i+j]);
      printf("%*s ", print_len, number_buffer);
    }
    printf("\n");
  }
  printf("\n");
}


int main(int argc, char const *argv[])
{

  // build matrices
  int matrix_width = atoi(argv[1]);
  int matrix_size = matrix_width*matrix_width;
  double A[matrix_size];
  double B[matrix_size];
  double C[matrix_size];

  if (!strcmp(argv[2], "inc_dec_ones")) {
    // all ones
    // 1 ... 1
    for (int i = 0; i < matrix_size; i++)
      C[i] = 1;

    // increasing order
    // 1 ... N*N
    for (int i = 0; i < matrix_size; i++)
      A[i] = i+1;

    // decreasing
    // N*N ... 1
    for (int i = 0; i < matrix_size; i++)
      B[matrix_size-i-1] = i+1;

  } else if (!strcmp(argv[2], "random")) {
    // random distribution
    srand(time(NULL));

    for (int i = 0; i < matrix_size; i++) {
      A[i] = (rand() / (double)RAND_MAX)*2 - 1.0;
    }
      
    // making all matrices the same
    memcpy(B, A, sizeof(double)*matrix_size);
    memcpy(C, A, sizeof(double)*matrix_size);
  }



  #ifdef PRINT

  // print_matrix(matrix_width, A, var(A));
  // print_matrix(matrix_width, B, var(B));
  // print_matrix(matrix_width, C, var(C));

  #endif /* PRINT */

  // run
  square_dgemm(matrix_width, A, B, C);
  
  

  #ifdef PRINT

  print_matrix(matrix_width, C, "OUTPUT");

  #endif /* PRINT */
  
  return 0;
}

