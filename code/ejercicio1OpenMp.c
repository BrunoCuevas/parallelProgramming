#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int main(int argc, char *argv[]) {
	int X = atoi(argv[1]);
	int T = atoi(argv[2]);
	// oS : operation-matrix Size
	int oS = 3;
	double *U = malloc(sizeof(double)*(X+1)*3);
	int t, x;
	double L= 0.345678, S;
	// initialize positions of matrix U
	for (x=1; x<X; x++) {
		U[x] = sin(x*M_PI/(double)X);
		U[x + X + 1] = U[x] * cos(M_PI /(double)T);
	}
	for (t=0; t<oS; t++) {
		U[t*(X+1)] = U[t*(X+1) + X] = 0.0;
	}
	// Program Body
		// tS : timeStep
		// iX : iterX
		// fstTerm : First term of the equation
		// sndTerm : Second term of the equation
		// trdTerm : Third term of the equation
		// fthTerm : Fourth term of the equation
		// iRXL : index X for relocation
		// iRTL : index T for relocation
	int tS, iX, address, iRXL;
	double fstTerm, sndTerm, trdTerm, fthTerm;


	
	for (tS = 1; tS < T + 2; tS ++) {
		#pragma omp parallel default(none) shared(tS, T, U, L, X) private(address, fstTerm, sndTerm, trdTerm, fthTerm, iX, iRXL) 
{
			#pragma omp for nowait
			for (iX = 1; iX < X ; iX ++) {
				address = ((X+1)) + iX;
				fstTerm = 2*(1-L)*U[address];
				sndTerm = L*U[address + 1];
				trdTerm = L*U[address - 1];
				fthTerm = -U[address - (X+1)];
				U[address + (X+1)] = fstTerm + sndTerm + trdTerm + fthTerm ;

			}
			#pragma omp barrier
			#pragma omp for nowait
			for (iRXL = 1 ; iRXL < X ; iRXL ++) {
				U[iRXL] = U[iRXL + X + 1];
				U[iRXL + X + 1] = U[iRXL + 2*(X+1)];
			}
		}
	}	
	
	 
	// obtain checksum of final state
		// cS : checkSum for a given value
	S = 0;
	int fP = (X+1);
	for (iX = 0; iX <= X; iX ++){
		S = S + U[fP + iX];
	}
	printf("CheckSum = %e\n", S);
	return 0;
}
