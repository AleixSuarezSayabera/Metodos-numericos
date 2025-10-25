#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void intnev_avald(double x, int n, double xi[], double yi[], double *p, double *dp) {
    double P[n+1];
    double dP[n+1];

    for (int i = 0; i <= n; i++) {
        P[i] = yi[i];
        dP[i] = 0.0;
    }

    for (int j = 1; j <= n; j++) {
        for (int i = 0; i <= n - j; i++) {
            P[i] = ((x-xi[i]) * P[i+1] - (x - xi[i+j]) * P[i]) / (xi[i+j]-xi[i]);
            dP[i] = (P[i+1]-P[i])/(xi[i+j]-xi[i]) + (dP[i+1]*(x-xi[i])-dP[i]*(x-xi[i+j]))/(xi[i+j]-xi[i]);
        }
    }

    if (p != NULL) {
        *p = P[0];
    }
    if (dp != NULL) {
        *dp = dP[0];
    }
}