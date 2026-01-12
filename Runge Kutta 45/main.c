#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcions.h"


int main(int argc, char *argv[])
{
    if (argc != 12) {
        fprintf(stderr, "Pr3Ex3 x0 y0 z0 beta rho sigma h hmin hmax tol T\n");
        return -1;
    }

    double *prm=malloc(3*sizeof(double));
    double *x=malloc(3*sizeof(double));
    int n=3;

    x[0]=atof(argv[1]);
    x[1]=atof(argv[2]);
    x[2]=atof(argv[3]);

    prm[0]=atof(argv[4]);
    prm[1]=atof(argv[5]);
    prm[2]=atof(argv[6]);

    double hmin=atof(argv[8]);
    double hmax=atof(argv[9]);
    double h=atof(argv[7]);
    double tol=atof(argv[10]);
    double T=atof(argv[11]);

    double t=0;

    FILE *fp = fopen("atractor.txt","w");

    while(t<T){
        if (t + h > T) h = T - t;
        fprintf(fp,"%f %f %f %f\n",t, x[0],x[1],x[2]);
        rk45(&t,x,&h,hmin,hmax,tol,n,camp,prm);
    }
    fprintf(fp,"%f %f %f %f\n",t, x[0],x[1],x[2]);

    fclose(fp);
    free(prm);
    free(x);

    return 0;
}


int camp(int n, double t, double *x, double *f, double *prm){
    double beta=prm[0];
    double rho=prm[1];
    double sigma=prm[2];
    f[0]=sigma*(x[1]-x[0]);
    f[1]=rho*x[0]-x[1]-x[0]*x[2];
    f[2]=-beta*x[2]+x[0]*x[1];
    return 0;
}
