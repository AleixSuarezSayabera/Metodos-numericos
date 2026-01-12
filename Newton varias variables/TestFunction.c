#include <stdio.h>
#include <math.h>

int function1(int m, int n, double *x, double *f, double *df, void *prm)
{
	if (m!=2||n!=2){
		printf("function1():: Error en les dimensions de la funció F.\n");
		return -1;
	}
	#define X1 x[0]
	#define X2 x[1]
	#define F1 f[0]
	#define F2 f[1]
	#define DF(i,j) df[(i)+(m)*(j)] /* i=fila, j=columna */
	F1 = X1*X1*X1-3*X1*X2*X2-1;
	F2 = 3*X1*X1*X2-X2*X2*X2;
	DF(0,0) = 3*X1*X1-3*X2*X2;
	DF(0,1) = -6*X1*X2;
	DF(1,0) = 6*X1*X2;
	DF(1,1) = 3*X1*X1-3*X2*X2;
	#undef X1
	#undef X2
	#undef X3
	#undef F1
	#undef F2
	#undef F3
	#undef DF
	return 0;
}
