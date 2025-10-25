#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "trigrec.h"
#include "temps.h"

int main (int argc, char *argv[]) {
   int k;
   double x;
   if (argc!=3
         || sscanf(argv[1],"%d",&k)!=1
         || sscanf(argv[2],"%lf",&x)!=1
         ) {
      fprintf(stderr, "trigrec_escr k x\n");
      return -1;
   }
   
   double *c0;
    double *s0;
    c0 = (double *)malloc((k + 1) * sizeof(double));
    s0 = (double *)malloc((k + 1) * sizeof(double));
    assert(c0 != NULL && s0 != NULL);

    double tt0 = -1.0;

    double tt1 = temps(&tt0);
    trigrec0(k, x, c0, s0);
    double tt2 = temps(&tt0);

    printf("temps trigrec0: %.16g segons\n", tt2 - tt1);

    double *c1;
    double *s1;
    c1 = (double *)malloc((k + 1) * sizeof(double));
    s1 = (double *)malloc((k + 1) * sizeof(double));
    assert(c1 != NULL && s1 != NULL);

    double tt3 = temps(&tt0);
    trigrec1(k, x, c1, s1);
    double tt4 = temps(&tt0);

    printf("temps trigrec1: %.16g segons\n", tt4 - tt3);

    double *c2;
    double *s2;
    c2 = (double *)malloc((k + 1) * sizeof(double));
    s2 = (double *)malloc((k + 1) * sizeof(double));
    assert(c2 != NULL && s2 != NULL);

    double tt5 = temps(&tt0);
    trigrec2(k, x, c2, s2);
    double tt6 = temps(&tt0);

    printf("temps trigrec2: %.16g segons\n", tt6 - tt5);

    double *c3;
    double *s3;
    c3 = (double *)malloc((k + 1) * sizeof(double));
    s3 = (double *)malloc((k + 1) * sizeof(double));
    assert(c3 != NULL && s3 != NULL);

    double tt7 = temps(&tt0);
    trigrec3(k, x, c3, s3);
    double tt8 = temps(&tt0);

    printf("temps trigrec3: %.16g segons\n", tt8 - tt7);

   double errc1 = 0, errs1 = 0;
   double errc2 = 0, errs2 = 0;
   double errc3 = 0, errs3 = 0;

    for (int i = 0; i <= k; i++) {
        double erc1 = (c1[i] - c0[i]);
        double ers1 = (s1[i] - s0[i]);
        double erc2 = (c2[i] - c0[i]);
        double ers2 = (s2[i] - s0[i]);
        double erc3 = (c3[i] - c0[i]);
        double ers3 = (s3[i] - s0[i]);
        erc1 = fabs(erc1);
        erc2 = fabs(erc2);
        erc3 = fabs(erc3);
        ers1 = fabs(ers1);
        ers2 = fabs(ers2);
        ers3 = fabs(ers3);
        if (erc1 > errc1) errc1 = erc1;
        if (ers1 > errs1) errs1 = ers1;
        if (erc2 > errc2) errc2 = erc2;
        if (ers2 > errs2) errs2 = ers2;
        if (erc3 > errc3) errc3 = erc3;
        if (ers3 > errs3) errs3 = ers3;
    }

    printf("errc1 %.16g errc2 %.16g errc3 %.16g\n", errc1, errc2, errc3);
    printf("errs1 %.16g errs2 %.16g errs3 %.16g\n", errs1, errs2, errs3);

    free(c0);
    free(s0);
    free(c1);
    free(s1);
    free(c2);
    free(s2);
    free(c3);
    free(s3);
   return 0;
}