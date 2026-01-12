#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define MAT(i,j) A[(i) + (j)*(m)]


int QRsolve (int m, int n, double *A, double *b, double *tau, double *x, double tol){
    int kmax = n;
    if (n == m) kmax = n - 1;

    for (int k = 0; k < kmax; k++) {
        double sk = 0;
        for(int i=k; i<m; i++){
            sk += MAT(i,k)*MAT(i,k);
        }
        if(sk < tol){
            return -1;
        }
        sk = sqrt(sk);
        if (MAT(k,k) > 0){
            sk = -sk;
        }

        tau[k] = MAT(k,k) - sk;

        for(int i=k+1; i<m; i++){
            MAT(i,k) /= tau[k];
        }
        tau[k] = -tau[k] / sk;
        MAT(k,k) = sk;

        for(int j=k+1; j<n; j++){
            double beta = MAT(k,j);
            for(int i=k+1; i<m; i++){
                beta += MAT(i,k)*MAT(i,j);
            }
            beta *= tau[k];

            MAT(k,j) -= beta;
            for(int i=k+1; i<m; i++){
                MAT(i,j) -= beta * MAT(i,k);
            }
        }

        double beta = b[k];
        for(int i=k+1; i<m; i++){
            beta += MAT(i,k)*b[i];
        }
        beta *= tau[k];
        b[k] -= beta;
        for(int i=k+1; i<m; i++){
            b[i] -= beta*MAT(i,k);
        }
    }

    for(int i=n-1; i>=0; i--){
        double aux = 0;
        for(int j=i+1; j<n; j++){
            aux += MAT(i,j)*x[j];
        }
        x[i] = (b[i] - aux) / MAT(i,i);
    }

    return 0;
}
