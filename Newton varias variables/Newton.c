#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double * newton (int m, int n, double *x,
                 int (*fdf)(int m, int n,double *x, double *f, double *df,void *prm),
                 void *prm, int maxit, double tol){

    double *f = malloc(m*sizeof(double));
    double *df = malloc(n*m*sizeof(double));
    double *tau = malloc(m * n * sizeof(double));
    double *y   = malloc(n * sizeof(double));

    for(int k=0;k<maxit;k++){
    fdf(m,n,x,f,df,prm);
    double normf = 0;
    for(int i=0; i<m; i++) normf += f[i]*f[i];
    normf = sqrt(normf);
    if(normf < tol) break;
    QRsolve(m, n, df, f, tau, y, tol);
    for(int i=0;i<n;i++){
        x[i]=x[i]-y[i];
    }
    }

    free(tau);
    free(y);
    free(f);
    free(df);

    return x;
}


