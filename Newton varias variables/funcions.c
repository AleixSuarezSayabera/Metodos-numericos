#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define A(i,j) A[(i)+(j)*(m)]


int QRsolve (int m, int n, double *A, double *b, double *tau, double *x, double tol){
    int kmax = n;
    if (n == m) kmax = n - 1;

    for (int k = 0; k < kmax; k++) {
        double sk = 0;
        for(int i=k; i<m; i++){
            sk += A(i,k)*A(i,k);
        }
        if(sk < tol){
            return -1;
        }
        sk = sqrt(sk);
        if (A(k,k) > 0){
            sk = -sk;
        }

        tau[k] = A(k,k) - sk;

        for(int i=k+1; i<m; i++){
            A(i,k) /= tau[k];
        }
        tau[k] = -tau[k] / sk;
        A(k,k) = sk;

        for(int j=k+1; j<n; j++){
            double beta = A(k,j);
            for(int i=k+1; i<m; i++){
                beta += A(i,k)*A(i,j);
            }
            beta *= tau[k];

            A(k,j) -= beta;
            for(int i=k+1; i<m; i++){
                A(i,j) -= beta * A(i,k);
            }
        }

        double beta = b[k];
        for(int i=k+1; i<m; i++){
            beta += A(i,k)*b[i];
        }
        beta *= tau[k];
        b[k] -= beta;
        for(int i=k+1; i<m; i++){
            b[i] -= beta*A(i,k);
        }
    }

    for(int i=n-1; i>=0; i--){
        double aux = 0;
        for(int j=i+1; j<n; j++){
            aux += A(i,j)*x[j];
        }
        x[i] = (b[i] - aux) / A(i,i);
    }

    return 0;
}


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


