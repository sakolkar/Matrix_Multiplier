#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void check_usage(int);

int main(int argc, char* argv[]) {
	check_usage(argc);

	int number_of_threads = atoi(argv[1]);
	printf("%d\n", number_of_threads);

	return 0;
}

void check_usage(int argc) {
	if (argc != 2) {
		fprintf(stderr,
			"Usage: Takes 1 arguments for number of threads\n");
		exit(EXIT_FAILURE);
	}
}
