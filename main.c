#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "lab1_IO.h"
#include "timer.h"

// Global variables
int** matrix_a;
int** matrix_b;
int** matrix_c;
int   matrix_size;
int   number_of_threads; // p

// function signatures
void    check_usage(int);
int     get_x(int);
int     get_y(int);
int     get_upper_bound(int);
int     get_lower_bound(int);
void*   threadfunc(void*);

int main(int argc, char* argv[]) {

	long thread_index;
	int i;
	double start, end;

	check_usage(argc);
	number_of_threads = atoi(argv[1]);

	pthread_t* thread_handles;
	thread_handles = malloc( number_of_threads * sizeof *thread_handles );

	Lab1_loadinput( &matrix_a,
			&matrix_b,
			&matrix_size );

	matrix_c = malloc( matrix_size * sizeof *matrix_c);

	for (i = 0; i < matrix_size; i++)
		matrix_c[i] = malloc( matrix_size * sizeof *matrix_c[i]);

	GET_TIME(start);
	for (thread_index = 0; thread_index < number_of_threads; thread_index++)
		pthread_create( &thread_handles[thread_index],
				NULL,
				threadfunc,
				(void*) thread_index );

	for (thread_index = 0; thread_index < number_of_threads; thread_index++)
		pthread_join( thread_handles[thread_index], NULL );
	GET_TIME(end);

	Lab1_saveoutput( matrix_c, &matrix_size, (end-start) );
	free(thread_handles);
	// TODO: free inner matrix elements

	return 0;
}

void check_usage(int argc) {
	if (argc != 2) {
		fprintf(stderr,
			"Usage: Takes 1 arguments for number of threads\n");
		exit(EXIT_FAILURE);
	}
}

void* threadfunc(void* arg_p) {
	long rank = (long) arg_p;
	int lower_bound_x = get_lower_bound(get_x(rank));
	int upper_bound_x = get_upper_bound(get_x(rank));
	int lower_bound_y = get_lower_bound(get_y(rank));
	int upper_bound_y = get_upper_bound(get_y(rank));
	int i = 0, j = 0, k = 0;
	for (i = lower_bound_x; i <= upper_bound_x; i++) {
		for(j = lower_bound_y; j <= upper_bound_y; j++) {
			matrix_c[i][j] = 0;
			for (k = 0; k < matrix_size; k++)
				matrix_c[i][j] +=   matrix_a[i][k]
						  * matrix_b[k][j];
		}
	}

	printf("my rank: %ld\n", (long) arg_p); // TODO: get rid of me
	return NULL;
}

int get_lower_bound(int coordinate) {
	return (int) (matrix_size * coordinate / sqrt(number_of_threads));
}

int get_upper_bound(int coordinate) {
	// upper bound is 1 less than lower bound of higher coordinate
	return (int) get_lower_bound(coordinate+1) - 1;
}

int get_x(int rank) {
	return (int) floor(rank/sqrt(number_of_threads));
}

int get_y(int rank) {
	return (int) (rank % (int) sqrt(number_of_threads));
}
