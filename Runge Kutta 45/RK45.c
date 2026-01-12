#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int rk45 (double *t, double *x, double *h, double hmin, double hmax,
          double tol, int n, int (*camp)(int n, double t, double *x,
          double *f, double *prm), double *prm) {
	/*Coeficients RK45 (estatics)*/
	static double c[6] = {0., 1./4., 3./8., 12./13., 1., 1./2.};
	static double A[15] = {1./4., 3./32., 9./32., 1932./2197.,
		-7200./2197.,7296./2197., 439./216., -8., 3680./513.,
		-845./4104., -8./27., 2., -3544./2565., 1859./4104., -11./40.};
	static double b[6] = {25./216., 0., 1408./2565., 2197./4104., -1./5.,0.};
	static double bp[6] = {16./135., 0., 6656./12825., 28561./56430., -9./50., 2./55.};
	static double E[6] = {-1./360., 0., 128./4275., 2197./75240., -1./50., -2./55.};

	double **k = malloc(6 * sizeof(double*));
    for (int j = 0; j < 6; j++) {
        k[j] = malloc(n * sizeof(double));
    }
    double *Fbp=malloc(n*sizeof(double));
	double *f=malloc(n*sizeof(double));
	double *xaux=malloc(n*sizeof(double));
	double *xb=malloc(n*sizeof(double));
	double *xbp=malloc(n*sizeof(double));

    //pas 1
	for(int i=0;i<n;i++){
        xaux[i]=x[i];
	}

	camp(n,*t+c[0],xaux,f,prm);
	for(int i=0;i<n;i++){
	k[0][i]= f[i];
	}

	while(1){
        //pas 2
        for(int i=0;i<n;i++){
            xaux[i]=x[i]+(*h)*(A[0]*k[0][i]);
        }
        camp(n,*t + c[1]*(*h),xaux,f,prm);
        for(int i=0;i<n;i++){
        k[1][i]= f[i];
        }

        //pas 3
        for(int i=0;i<n;i++){
            xaux[i]=x[i]+(*h)*(A[1]*k[0][i]+A[2]*k[1][i]);
        }
        camp(n,*t + c[2]*(*h),xaux,f,prm);
        for(int i=0;i<n;i++){
        k[2][i]= f[i];
        }

        //pas 4
        for(int i=0;i<n;i++){
            xaux[i]=x[i]+(*h)*(A[3]*k[0][i]+A[4]*k[1][i]+A[5]*k[2][i]);
        }
        camp(n,*t + c[3]*(*h),xaux,f,prm);
        for(int i=0;i<n;i++){
        k[3][i]= f[i];
        }

        //pas 5
        for(int i=0;i<n;i++){
            xaux[i]=x[i]+(*h)*(A[6]*k[0][i]+A[7]*k[1][i]+A[8]*k[2][i]+A[9]*k[3][i]);
        }
        camp(n,*t + c[4]*(*h),xaux,f,prm);
        for(int i=0;i<n;i++){
        k[4][i]= f[i];
        }

        //pas 6
        for(int i=0;i<n;i++){
            xaux[i]=x[i]+(*h)*(A[10]*k[0][i]+A[11]*k[1][i]+A[12]*k[2][i]+A[13]*k[3][i]+A[14]*k[4][i]);
        }
        camp(n,*t + c[5]*(*h),xaux,f,prm);
        for(int i=0;i<n;i++){
        k[5][i]= f[i];
        }

        for(int i=0;i<n;i++){
            Fbp[i]= bp[0]*k[0][i]+bp[1]*k[1][i]+bp[2]*k[2][i]+bp[3]*k[3][i]+bp[4]*k[4][i]+bp[5]*k[5][i];
        }
        for (int i=0; i<n; i++) {
            xbp[i]=x[i]+(*h)*Fbp[i];
        }
        double err = 0.0;
        for (int i = 0; i < n; i++) {
            double e = 0.0;
            for (int j = 0; j < 6; j++) {
                e += E[j] * k[j][i];
            }
            e = fabs((*h) * e);
            if (e > err) err = e;
        }

        if (err == 0.0) err = tol / 10.0;

        double alpha = 0.9;
        double hnew = alpha * (*h) * pow(tol / err, 1.0 / 5.0);

        if (fabs(hnew) > hmax) hnew = copysign(hmax, hnew);
        if (fabs(hnew) < hmin) {
            printf("Error: no se puede calcular con la precisi n requerida (h < hmin)\n");
            return -1;
        }

        if (err <= tol) {
            *t += *h;
            for (int i = 0; i < n; i++) {
                x[i] = xbp[i];
            }
            *h = hnew;
            break;
        } else {
            *h = hnew;
        }
	}

	for (int j = 0; j < 6; j++) {
        free(k[j]);
    }
    free(k);
	free(Fbp);
	free(f);
	free(xaux);
	free(xb);
	free(xbp);

	return 0;
}

