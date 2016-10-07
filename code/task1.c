#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#define X 10000
//#define T 10000
//static double U[X+1][T+2];
 // declare matrix U

int main(int argc, char *argv[]) {
	int X = atoi(argv[1]);
	int T = atoi(argv[2]);
	int sizeNumber = (X+1)*(T+2);
	printf("size of the vector = %d \n", sizeNumber);
	double *U = malloc(sizeof(double)*(X+1)*(T+3));
	//double U = puntero;
	int startTime = clock();
	int t, x;
	double L= 0.345678, S;
	// initialize positions of matrix U
	for (x=1; x<X; x++) {
		U[x] = sin(x*M_PI/(double)X);
		U[x + X + 1] = U[x] * cos(M_PI /(double)T);
	}
	for (t=0; t<=T; t++) {
		U[t*(X+1)] = U[t*(X+1) + X] = 0.0;
	}
	printf("Hola!\n");
	// Program Body
		// tS : timeStep
		// iX : iterX
		// fstTerm : First term of the equation
		// sndTerm : Second term of the equation
		// trdTerm : Third term of the equation
		// fthTerm : Fourth term of the equation
	int tS, iX, address;
	double fstTerm, sndTerm, trdTerm, fthTerm;
	printf("Hola\n");
	for (tS = 1; tS < T + 2; tS ++) {
		for (iX = 1; iX < X ; iX ++) {
			address = (tS*(X+1)) + iX;
			fstTerm = 2*(1-L)*U[address];
			sndTerm = L*U[address + 1];
			trdTerm = L*U[address - 1];
			fthTerm = -U[address - (X+1)];
			if (tS > T) {
				printf("tS =%d \t iX =%d \t address = %d \n", tS, iX, address);
				printf("nex term = %d\n", address + X + 1);
			}
			U[address + (X+1)] = fstTerm + sndTerm + trdTerm + fthTerm ;
		}
	}
	printf("Hola!\n");
	// obtain checksum of final state
		// cS : checkSum for a given value
	S = 0;
	int fP = (T+1)*(X+1);
	for (iX = 0; iX <= X; iX ++){
		S = S + U[fP + iX];
	}
	printf("CheckSum = %e\n", S);
	int endTime = clock();
	printf("Time elapsed = %d\n", endTime - startTime);
	return 0;
}
