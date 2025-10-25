#include <stdio.h>
#include "rtbp.h"

#define PMAX .5
#define MU 1.215058560962404e-2

int main (int argc, char *argv[]) {
   double c, x0, xf;
   int isgn, n;

   if (argc<6
         || sscanf(argv[1], "%lf", &c)!=1
         || sscanf(argv[2], "%d", &isgn)!=1
         || sscanf(argv[3], "%lf", &x0)!=1
         || sscanf(argv[4], "%lf", &xf)!=1
         || sscanf(argv[5], "%d", &n)!=1
      ) {
      fprintf(stderr,"%s c isgn x0 xf n \
\n\
", argv[0]);
      return -1;
   }
   double u,xi,divisio;
   divisio = (xf-x0)/n;
for (int i=0;i<=n;i++){
   xi = x0+i*divisio;
   proptraj(MU,1,c,isgn,xi,&u,NULL,PMAX,NULL);
   printf("%.16g %.16g \n",xi,u);
}
}
