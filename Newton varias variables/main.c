#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcions.h"
#include "TestFunction.h"

int main()
{
    int m=2;
    int n=2;
    int maxit=20;
    double tol=1e-10;
    int punts=1000;
    double pas=2.0/(punts-1.0);

    double arrels[3][2]={
        {1,0},
        {-0.5,sqrt(3)/2},
        {-0.5,-sqrt(3)/2}
    };

    FILE *g1 = fopen("g1.txt", "w");
    FILE *g2 = fopen("g2.txt", "w");
    FILE *g3 = fopen("g3.txt", "w");

    double x_actual[2];
    double x_inicial[2];

    printf("Calculant...\n");

    for(int i=0;i<punts;i++){
        for(int j=0;j<punts;j++){
            x_inicial[0]=-1+i*pas;
            x_inicial[1]=-1+j*pas;

            x_actual[0]=x_inicial[0];
            x_actual[1]=x_inicial[1];

            newton(m,n,x_actual,function1,NULL,maxit,tol);

            for(int k=0;k<3;k++){
                double dist=sqrt(pow(x_actual[0]-arrels[k][0],2)+pow(x_actual[1]-arrels[k][1],2));
                if(dist<1e-4){
                    if(k==0) fprintf(g1, "%f %f\n", x_inicial[0], x_inicial[1]);
                    else if (k == 1) fprintf(g2, "%f %f\n", x_inicial[0], x_inicial[1]);
                    else if (k == 2) fprintf(g3, "%f %f\n", x_inicial[0], x_inicial[1]);
                    break;
                }
            }
        }
    }

    fclose(g1);
    fclose(g2);
    fclose(g3);
    printf("Fet\n");

    return 0;
}
