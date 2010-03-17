#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "interval.h"
#include "atomic.h"
#include "internal.h"

/* Basic constants and macros */
#define NEW(type) ((type *) malloc(sizeof(type)));
#define DELETE(ptr) (free(ptr));
#define THRESHOLD 13

int sequential_fibonacci(int n);
void parallel_fibonacci(int n, int *result);

int main(int argc, char *argv[])
{
	if(argc != 2) {
		fprintf(stderr, "Usage: fibonacci n\n");
		return 1;
	}

	const int n = atoi(argv[1]);

	int seq_solution = 0;
	time_t seq_time0 = time(NULL);
	seq_solution = sequential_fibonacci(n);
	time_t seq_time1 = time(NULL);
	time_t seq_timed = seq_time1 - seq_time0;

	printf("Seq. Solution: %d\n", seq_solution);
	printf("Seq. Processor Time: %ld second(s)\n", seq_timed);
	fflush(stdout);

	int *par_solution = NEW(int);
	*par_solution = 0;
	time_t par_time0 = time(NULL);
	root_interval(^(point_t *end) {
			parallel_fibonacci(n, par_solution);
		});
	time_t par_time1 = time(NULL);
	time_t par_timed = par_time1 - par_time0;

	assert(seq_solution == *par_solution);

	printf("Par. Solution: %d\n", *par_solution);
	printf("Par. Processor Time: %ld seconds\n", par_timed);
	DELETE(par_solution);

	printf("Par/Seq Ratio: %.3f\n", (1.0 * par_timed) / seq_timed);

	return 0;
}

int sequential_fibonacci(int n)
{
	if (n <= 1) {
		return n;
	}
	else {
		return sequential_fibonacci(n - 1) +
			sequential_fibonacci(n - 2);
	}
}

/*
  TODO: Doesn't work correctly with interval, using subinterval doesn't make
  any sense though...

  TODO: Needs HB relations...
*/
void parallel_fibonacci(int n, int *result) {
	if (n < 2) {
		*result = n;
	}
	else {
		int *result1 = NEW(int);
		*result1 = *result;
		subinterval(^(point_t *_) {
				parallel_fibonacci(n - 1, result1);
			});

		int *result2 = NEW(int);
		*result2 = *result;
		subinterval(^(point_t *_) {
				parallel_fibonacci(n - 2, result2);
			});

		*result = *result1 + *result2;
	}
}

