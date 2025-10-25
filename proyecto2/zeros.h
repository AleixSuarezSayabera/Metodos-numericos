double biseccio (double *a, double *b, double tol, double (*f)(double,void*),
      void *prm, int ixrr);
int newton (double *x, double tolf, double tolx, int maxit,
            void (*fdf)(double,double*,double*,void*),
            void *prm, int ixrr);