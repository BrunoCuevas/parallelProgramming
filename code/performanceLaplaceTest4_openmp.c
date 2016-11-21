#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define n 4096
#define m 4096
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
	float *ls = malloc(sizeof(float)*m*n);
	float *nls = malloc(sizeof(float)*m*n);
	int index ;
    for (i = 1; i < n; i++) {
		for (j=1; j < m;j++){
			index = ((i-1)*n) + j;
			ls[index] = A[i][j];
			nls[index]=Anew[i][j];
		}
    }
	printf("we got here\n");
	int inR; int inL; int inD; int inU;
    while ( error > tol && iter < iter_max )
    {

		error = 0.f;
		#pragma omp parallel default(none) shared(ls, nls, iter) \
		private(i,j,index, inL, inU, inD, inR) \
		reduction(max:error)
		{

				#pragma omp for nowait
				for (index = 0; index < n*m; index ++) {
					i = trunc(index/n) + 1;
					j = index - (i-1)*n;
					if (((i-1)*(n-i)*(j-1)*(m-j)) == 0) {
						continue;
					} else {
						inU = index - n;
						inD = index + n;
						inL = index - 1;
						inR = index + 1;

				    	nls[index] = (ls[inU] + ls[inD] + ls[inL] + ls[inR])*0.25f;
				    	error = fabsf(nls[index]-ls[index] )  ;
					}

				}
				#pragma omp barrier
				for (index = 0; index < n*m; index ++) {
					i = trunc(index/n) + 1;
					j = index - (i-1)*n;
					if (((i-1)*(n-i)*(j-1)*(m-j)) == 0) {
						continue;
					} else {
						ls[index] = nls[index];
					}
				}

		}

	    iter++;
		error = sqrt(error);
	    if(iter % (iter_max/10) == 0) printf("%5d, %0.6f\n", iter, error);


    }
}
