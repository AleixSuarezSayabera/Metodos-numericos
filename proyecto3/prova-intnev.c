#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "intnev.h"

double PI = 3.14159265358979323846;

int main() {
    int n = 9;
    double xi[] = {0, PI/8, PI/4, 3*PI/8, PI/2, 5*PI/8, 3*PI/4, 7*PI/8, PI};
    double yi[n];

    for (int i = 0; i < n; i++) {
        yi[i] = sin(xi[i])*cos(xi[i]);
    }
    double x;
    printf("Valor de x= ");
    scanf("%lf", &x);

    if (x < 0 || x > PI) {
        printf("El valor de x ha d'estar a [0, PI].\n");
        return 1;
    }
    double p, dp;

    intnev_avald(x, n-1, xi, yi, &p, &dp);
    printf("Interpolació de sin(x)cos(x) en x = %lf\n", x);
    printf("p = %.16g\n", p);
    printf("dp = %.16g\n", dp);
    printf("Valor real de f(x) = %.16g\n", sin(x)*cos(x));
    printf("Valor real de f'(x) = %.16g\n", cos(2*x));
    printf("Error en f(x): %.16g\n", fabs(p - sin(x)*cos(x)));
    printf("Error en f'(x): %.16g\n", fabs(dp - cos(2*x)));
    return 0;
}