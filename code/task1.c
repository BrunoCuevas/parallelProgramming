#include <stdio.h>
#include <math.h>
#define X 10000
#define T 10000
static double U[X+1][T+2];
 // declare matrix U
	int main() {
	int t, x;
	double L= 0.345678, S;
	// initialize positions of matrix U
	for (x=1; x<X; x++) {
		U[x][0] = sin(x*M_PI/(double)X);
		U[x][1] = U[x][0] * cos(M_PI /(double)T);
	}
	for (t=0; t<=T; t++) {
		U[0][t] = U[X][t] = 0.0;
	}
	// Program Body
		// tS : timeStep
		// iX : iterX
		// fstTerm : First term of the equation
		// sndTerm : Second term of the equation
		// trdTerm : Third term of the equation
		// fthTerm : Fourth term of the equation
	int tS, iX;
	float fstTerm, sndTerm, trdTerm, fthTerm;
	for (tS = 1; tS < T + 2; tS ++) {
		for (iX = 1; iX < X ; iX ++) {
			fstTerm = 2*(1-L)*U[iX][tS];
			sndTerm = L*U[iX + 1][tS];
			trdTerm = L*U[iX - 1][tS];
			fthTerm = -U[iX][tS - 1];
			U[iX][tS +1] = fstTerm + sndTerm + trdTerm + fthTerm ;
		}
	}
	// obtain checksum of final state
		// cS : checkSum for a given value
	float cS;
	for (iX = 0; iX <= X; iX ++){
		cS = 0;
		for (tS = 0; tS <= T + 2; tS ++) {
			cS =+ U[iX][tS];
		}
		S =+ cS;
	}
	printf("CheckSum = %e\n", S);
	return 0;
}
