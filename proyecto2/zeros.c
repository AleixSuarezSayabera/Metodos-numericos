#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double biseccio(double *a, double *b, double tol, double (*f)(double,void*),
                void *prm, int ixrr) {
    double p;
    double ai = *a;
    double bi = *b;
    int n = 0;
    double fa=(*f)(*a, prm);
    while ((bi - ai) / pow(2, n) >= tol) {
        p = (*a + *b) / 2;
        double fp=f(p,prm);
        if (ixrr != 0) {
            fprintf(stderr, "Iteració %d. Nou interval [a, b]: [%.16g, %.16g]\n", n + 1, *a, *b);
        }
        if (fa * fp <= 0) {
            *b = p;
        } else {
            *a = p;
            fa = fp;
        }
        n++;
    }
    return p;
}


int newton (double *x, double tolf, double tolx, int maxit,
            void (*fdf)(double,double*,double*,void*),
            void *prm, int ixrr) {
                double a,f,df;
                fdf(*x,&f,&df,prm);
                  for(int i=0;i<=maxit-1;i++){
                        a = f/df;
                        *x=*x-a;
                        fdf(*x,&f,&df,prm);
                        if (ixrr != 0) {
                            fprintf(stderr, "Iteració %d, nova aproximació: %.16g \n", i+1, *x);}
                        if ((fabs(f)<=tolf) && (fabs(a)<=tolx)){
                             return i+1;}
                  }
    return -1;
}

