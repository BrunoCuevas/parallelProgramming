#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef n
#define n 4096
#endif
#ifndef m
#define m 4096
#endif

float A[n][m];
float Anew[n][m];
float y[n];

int main(int argc, char** argv)
{
    int i, j;
    int iter_max = 1000;

    const float pi  = 2.0f * asinf(1.0f);
    const float tol = 3.0e-3f;
    float error= 1.0f;

    // obtener argumentos proporcionados en tiempo de ejecucion
    if (argc>1) {  iter_max = atoi(argv[1]); }

    memset(A, 0, n * m * sizeof(float));

    //  set boundary conditions
    for (i=0; i < m; i++)
    {
       A[0][i]   = 0.f;
       A[n-1][i] = 0.f;
    }

    for (j=0; j < n; j++)
    {
       y[j] = sinf(pi * j / (n-1));
       A[j][0] = y[j];
       A[j][m-1] = y[j]*expf(-pi);
    }

    printf("Jacobi relaxation Calculation: %d x %d mesh, maximum of %d iterations\n",
           n, m, iter_max );

    int iter = 0;

    for (i=1; i < m; i++)
    {
       Anew[0][i]   = 0.f;
       Anew[n-1][i] = 0.f;
    }

    for (j = 1; j < n; j++)
    {
       Anew[j][0]  = y[j];
       Anew[j][m-1]= y[j]*expf(-pi);
    }

    while ( error > tol && iter < iter_max )
    {
       error = 0.f;

	if(iter % 2 == 0){
		for( j=1; j < n-1; j++)
	   		for( i=1; i < m-1; i++ ){
	        	Anew[j][i] = ( A[j][i+1]+A[j][i-1]+A[j-1][i]+A[j+1][i])*0.25f;
	        	error = fmaxf( error,  fabsf( Anew[j][i]-A[j][i] )  );
			}
	}
	else {
       		for( j=1; j < n-1; j++)
	   	for( i=1; i < m-1; i++ ){
	              	A[j][i] = ( Anew[j][i+1]+Anew[j][i-1]+Anew[j-1][i]+Anew[j+1][i])*0.25f;
	              	error = fmaxf( error,  fabsf( Anew[j][i]-A[j][i] )  );
          	}
	}


       iter++;
	error = sqrt(error);
       if(iter % (iter_max/10) == 0) printf("%5d, %0.6f\n", iter, error);

    }
}
