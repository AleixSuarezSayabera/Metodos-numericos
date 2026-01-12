#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "funcions.h"

#define A(i,j) A[(i)*n + (j)]

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Pr1Ex4 n\n");
        return -1;
    }
    int n=atoi(argv[1]);

    srand(time(0));

    double *A=malloc(n*n*sizeof(double));
    double *b=malloc(n*sizeof(double));
    double *tau=malloc(n*sizeof(double));
    double *sol=malloc(n*sizeof(double));

    for(int i=0;i<n*n;i++){
        A[i]=((double)rand())/RAND_MAX;
    }

    printf("La matriu aleatoria x es:\n");
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            printf("%f ",A(i,j));
        }
        printf("\n");
    }


    printf("El vector b es:\n");
    for (int i=0;i<n;i++) {
        double suma_fila=0;
        for (int j=0;j<n;j++) {
            suma_fila += A(i, j);
        }
        b[i] = suma_fila;
        printf("%f\n",b[i]);
    }

    double tol = 1e-12;
    int res = QRsolve(n, n, A, b, tau, sol, tol);

    if (res == 0) {
        printf("Solucio calculada:\n");
        for (int i = 0; i < n; i++) {
            printf("x[%d] = %f\n", i, sol[i]);
        }
    }
    else {
        printf("Error: El sistema no s'ha pogut resoldre\n");
    }

    double error=0;

    for (int i = 0; i < n; i++) {
        double dif = fabs(sol[i] - 1.0);
        if (dif > error) {
            error = dif;
        }
    }
    printf("Error maxim de determinacio: %e\n", error);

    free(A);
    free(b);
    free(tau);
    free(sol);

    return 0;
}
