#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>
double dboard(int rank, int darts) {
	srandom(time(NULL)+rank);
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
	return(score);
}
void main (int argc, char *argv[]) {
	int err = MPI_Init(&argc, &argv);
	int reps = 10000;
	int rank, count;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Status status;
	MPI_Comm_size(MPI_COMM_WORLD, &count);
	int scoreGather[count];
	int score;
	score = dboard(rank, reps/count);
	MPI_Gather(&score, 1, MPI_INTEGER, &scoreGather, 1, MPI_INTEGER, 0, MPI_COMM_WORLD); 
	if (rank == 0) {
		int piAverage = 0;
		int iter ;
		double pi;
		for (iter = 0 ; iter < count; iter ++) {
			piAverage += scoreGather[iter];
		}
		pi = (double) piAverage*4 / (reps);
		printf("pi = %f \n", pi);
	}
	err = MPI_Finalize();
}

