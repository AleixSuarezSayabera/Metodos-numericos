#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intnev.h"

int main(int argc, char *argv[]) {
    double vimg;
    int n, nimg;

    if (argc < 4
        || sscanf(argv[1], "%d", &n) != 1
        || sscanf(argv[2], "%d", &nimg) != 1
        || sscanf(argv[3], "%lf", &vimg) != 1) {
        fprintf(stderr, "%s n nimg vimg\n", argv[0]);
        return -1;
    }

    int m = 0;
    double x, y;
    while (scanf("%lf %lf", &x, &y) == 2) {
        m++;
    }

    fseek(stdin, 0, SEEK_SET);

    double *xi = (double *)malloc(m * sizeof(double));
    double *yi = (double *)malloc(m * sizeof(double));

    if (xi == NULL || yi == NULL) {
        fprintf(stderr, "Error de memòria\n");
        return -1;
    }

    for (int i = 0; i < m; i++) {
        if (scanf("%lf %lf", &xi[i], &yi[i]) != 2) {
            fprintf(stderr, "Error al llegir el fitxer\n");
            return -1;
        }
    }

    if (m < n + 1) {
        fprintf(stderr, "La n és massa gran\n");
        free(xi);
        free(yi);
        return -1;
    }

    int canvis = 0;
    int index_canvi = -1;
    for (int i = 0; i < m - 1; i++) {
        if ((yi[i] - vimg) * (yi[i + 1] - vimg) < 0) {
            canvis++;
            if (canvis == nimg) {
                index_canvi = i;
                break;
            }
        }
    }

    if (index_canvi == -1) {
        fprintf(stderr, "El nimg-èsim canvi de signe no s'ha trobat\n");
        free(xi);
        free(yi);
        return -1;
    }

    int k = index_canvi - n / 2;
    if (k < 0) k = 0;
    if (k + n >= m) k = m - n - 1;

    double *x_intp = &xi[k];
    double *y_intp = &yi[k];

    double p, error;
    intnev_avald(vimg, n, y_intp, x_intp, &p, NULL);
    intnev_avald(p, n, x_intp, y_intp, &error, NULL);

    printf("valor de la interpolació = %.16g\n", p);
    printf("Error estimat = %.16g\n", error);

    free(xi);
    free(yi);

    return 0;
}