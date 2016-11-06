#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
double dboard(int darts) {
	long random(void);
	double x_coord, y_coord, pi, r;
	int score, n;
	score = 0;
	/* "throw darts at board" */
	for (n = 1; n <= darts; n++) {
		/* generate random numbers for x and y coordinates */
		double res;
		r = (double)random()/(double)RAND_MAX;
		x_coord = (2.0 * r) - 1.0;
		r = (double)random()/(double)RAND_MAX;
		y_coord = (2.0 * r) - 1.0;
		/* if dart lands in circle, increment score */
		res = ((x_coord*x_coord) + (y_coord*y_coord));
		if (res <= 1.0) {
			score++;
		}
	}
	/* calculate pi */
	pi = 4.0 * (double)score/(double)darts;
	return(pi);
}
void main (int argc, char *argv[]) {
	int err = MPI_Init(&argc, &argv);
	int reps = 5000;
	int rank, count;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	double piInstance[1];
	piInstance[0] = dboard(reps);
	if (rank != 0) {
		MPI_Send(piInstance, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD);
	} else {
		MPI_Comm_size(MPI_COMM_WORLD, &count);
		double temp[1];
		temp[0]= 0;
		int iter;
		double averagedPi = 0 ;
		for (iter = 1; iter <=(count-1); iter ++ ) {
			MPI_Recv(temp, 1, MPI_DOUBLE, iter, 1, MPI_COMM_WORLD, &status);
			averagedPi = temp[0] + averagedPi;
			printf("process %d , pi = %f \n", status.MPI_SOURCE, temp[0]);
		}
		averagedPi = averagedPi + piInstance[0];
		averagedPi = averagedPi / count;
		printf("result = %f\n", averagedPi);

	}

	err = MPI_Finalize();
}
