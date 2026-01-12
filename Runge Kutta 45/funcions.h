#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rk45 (double *t, double *x, double *h, double hmin, double hmax,
          double tol, int n, int (*camp)(int n, double t, double *x,
          double *f, double *prm), double *prm);

int camp(int n, double t, double *x, double *f, double *prm);

