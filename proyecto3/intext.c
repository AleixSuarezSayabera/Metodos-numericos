#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "intnev.h"
#include "zeros.h"

struct f {
    int n;
    double *xi;
    double *yi;
};

double f_bis(double x, void *prm) {
    struct f *params = (struct f*) prm;
    double dp;
    intnev_avald(x, params->n, params->xi, params->yi, NULL, &dp);
    return dp;
}

int main(int argc, char *argv[]) {
   double tol;
   int n, next, ixrr;

   if (argc < 5 ||
        sscanf(argv[1], "%d", &n) != 1 ||
        sscanf(argv[2], "%d", &next) != 1 ||
        sscanf(argv[3], "%lf", &tol) != 1 ||
        sscanf(argv[4], "%d", &ixrr) != 1) {
        fprintf(stderr, "%s n next tol ixrr\n", argv[0]);
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
      fprintf(stderr, "La n és massa gran,no hi han tantes dades\n");
      free(xi);
      free(yi);
      return -1;
   }

   int zeros_trobats = 0;
   int index_zero = -1;
   for (int i = 1; i < m - 1; i++) {
      if ((yi[i - 1] < yi[i] && yi[i] > yi[i + 1]) || (yi[i - 1] > yi[i] && yi[i] < yi[i + 1])) {
         printf("index %d\n",i);
         zeros_trobats++;
         if (zeros_trobats == next) {
            index_zero = i;
            break;
         }
      }
   }

   if (index_zero == -1) {
      fprintf(stderr, "El %d-èsim zero de la derivada no s'ha trobat\n", next);
      free(xi);
      free(yi);
      return -1;
   }
    
   int k = index_zero - n / 2;
   if (k < 0) k = 0;
   if (k + n >= m) k = m - n - 1;

   double *x_intp = &xi[k];
   double *y_intp = &yi[k];

   double a = xi[index_zero];
   double b = xi[index_zero+1];

   struct f params = {n, x_intp, y_intp};
   double x0 = biseccio(&a, &b, tol, f_bis, &params, ixrr);

   printf("El zero de la derivada hi està en x = %.16g\n", x0);

   free(xi);
   free(yi);

   return 0;
}