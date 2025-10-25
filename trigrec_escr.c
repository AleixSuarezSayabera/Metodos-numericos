#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "trigrec.h"

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
   c0 = (double *)malloc((k+1)*sizeof(double));
   s0 = (double *)malloc((k+1)*sizeof(double)); 
   assert(c0 != NULL && s0 != NULL);
   trigrec0(k,x,c0,s0);

   double *c1;
   double *s1;
   c1 = (double *)malloc((k+1)*sizeof(double));
   s1 = (double *)malloc((k+1)*sizeof(double));
   assert(c1 != NULL && s1 != NULL);
   trigrec1(k,x,c1,s1);

   double *c2;
   double *s2;
   c2 = (double *)malloc((k+1)*sizeof(double));
   s2 = (double *)malloc((k+1)*sizeof(double));
   assert(c2 != NULL && s2 != NULL);
   trigrec2(k,x,c2,s2);

   double *c3;
   double *s3;
   c3 = (double *)malloc((k+1)*sizeof(double));
   s3 = (double *)malloc((k+1)*sizeof(double));
   assert(c3 != NULL && s3 != NULL);
   trigrec3(k,x,c3,s3);
   printf("Resultats per k = %d y x = %.16g:\n", k, x);
    for (int i = 0; i <= k; i++) {
        printf("c0[%d] = %.16g, c1[%d] = %.16g, c2[%d] = %.16g, c3[%d] = %.16g, \ns0[%d] = %.16g, s1[%d] = %.16g, s2[%d] = %.16g, s3[%d] = %.16g,\n", i, c0[i], i, c1[i], i, c2[i], i, c3[i], i, s0[i], i, s1[i], i, s2[i], i, s3[i]);
    }
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
