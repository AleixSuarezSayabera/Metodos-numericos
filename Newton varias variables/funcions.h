#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int QRsolve (int m, int n, double *A, double *b, double *tau, double *x, double tol);

double * newton (int m, int n, double *x,
                 int (*fdf)(int m, int n,double *x, double *f, double *df,void *prm),
                 void *prm, int maxit, double tol);

