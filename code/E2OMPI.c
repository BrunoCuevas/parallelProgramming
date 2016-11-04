#include <stdio.h>
#include <mpi.h>
void main (int argc, char *argv) {
	int err = MPI_Init(&argc, &argv);
	int reps = 500000;
	int rank, count;
	int MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	double piInstance = dboard(reps);
	if (rank != 0) {
		MPI_Send(piInstance, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	} else {
		MPI_COMM_SIZE(MPI_COMM_WORLD, &count);
		*piArray = malloc(double*count);
		int iter;
		double averagedPi ;
		for (iter = 1; iter <=(count-1), iter ++ ) {
			MPI_Recv(piArray[iter], 1, MPI_DOUBLE, iter, 1, MPI_COMM_WORLD, &status)
		}
		for (iter = 1; iter <=(count-1), iter ++ ) {
			averagedPi += piArray[iter];
		}
		averagedPi[count] = piInstance;
		averagedPi = averagedPi / count;
		printf("result = %f\n", averagedPi);

	}

	err = MPI_Finalize();
}
double dboard(int darts) {
	#define sqr(x) ((x)*(x))
	long random(void);
	double x_coord, y_coord, pi, r;
	int score, n;
	score = 0;
	/* "throw darts at board" */
	for (n = 1; n <= darts; n++) {
		/* generate random numbers for x and y coordinates */
		r = (double)random()/MAX_RAND;
		x_coord = (2.0 * r) - 1.0;
		r = (double)random()/MAX_RAND;
		y_coord = (2.0 * r) - 1.0;
		/* if dart lands in circle, increment score */
		if ((sqr(x_coord) + sqr(y_coord)) <= 1.0) {
			score++;
		}
	}
	/* calculate pi */
	pi = 4.0 * (double)score/(double)darts;
	return(pi);
}
