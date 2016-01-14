#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

#include "lab1_IO.h"

// Global variables
int*** matrix_a;
int*** matrix_b;
int*   matrix_size;
int    number_of_threads; // p

// function signatures
void    check_usage(int);
int     get_x(int);
int     get_y(int);
void*   threadfunc(void*);

int main(int argc, char* argv[]) {
	check_usage(argc);
	number_of_threads = atoi(argv[1]);

	pthread_t* thread_handles;
	thread_handles = malloc( number_of_threads * sizeof *thread_handles );

	long thread_index;
	for (thread_index = 0; thread_index < number_of_threads; thread_index++)
		pthread_create( &thread_handles[thread_index],
				NULL,
				threadfunc,
				(void*) thread_index );

	int a = Lab1_loadinput( matrix_a,
				matrix_b,
				matrix_size );

	for (thread_index = 0; thread_index < number_of_threads; thread_index++)
		pthread_join( thread_handles[thread_index], NULL );

	free(thread_handles);

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
	printf("my rank: %ld\n", (long) arg_p);
	return NULL;
}

int get_x(int rank) {
	return (int) floor(rank/sqrt(number_of_threads));
}

int get_y(int rank) {
	return (int) (rank % (int) sqrt(number_of_threads));
}
