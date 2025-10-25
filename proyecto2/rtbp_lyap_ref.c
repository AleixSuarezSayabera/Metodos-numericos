#include <stdio.h>
#include "rtbp.h"
#include "zeros.h"

#define MU 1.215058560962404e-2
#define PMAX .5

struct f {
   double c;
   int isgn;
};

double f_bis (double x, void *prm) {
   struct f *params = prm;
   double c;
   int isgn;
   c = (*params).c;
   isgn = (*params).isgn;
   double u;
   proptraj (MU, 1, c, isgn, x, &u, NULL, PMAX, NULL);
   return u;
}

void f_new ( double x, double *u, double *du, void *prm){
   struct f *params = prm;
   double c;
   int isgn;
   c = (*params).c;
   isgn = (*params).isgn;
   proptraj (MU, 1, c, isgn, x, u, du, PMAX, NULL);
}

int main (int argc, char *argv[]) {
   double c, xa, xb, tolbis, tolfnwt;
   int isgn, maxitnwt, ixrr;

   if (argc<9
         || sscanf(argv[1], "%lf", &c)!=1
         || sscanf(argv[2], "%d", &isgn)!=1
         || sscanf(argv[3], "%lf", &xa)!=1
         || sscanf(argv[4], "%lf", &xb)!=1
         || sscanf(argv[5], "%lf", &tolbis)!=1
         || sscanf(argv[6], "%lf", &tolfnwt)!=1
         || sscanf(argv[7], "%d", &maxitnwt)!=1
         || sscanf(argv[8], "%d", &ixrr)!=1
      ) {
      fprintf(stderr,"%s c isgn xa xb tolbis tolfnwt maxitnwt ixrr \
\n\
", argv[0]);
      return -1;

   }
   struct f params = {c, isgn};
   double x0;
   x0 = biseccio(&xa,&xb,tolbis,f_bis,&params,ixrr);
   newton(&x0,tolfnwt,10,maxitnwt,f_new,&params,ixrr);
   return 0;
}
