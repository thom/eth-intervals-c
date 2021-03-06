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
int parallel_fibonacci(int n);
interval_t hb_fibonacci(point_t *bound, int n, int *result);

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
      *par_solution = parallel_fibonacci(n);
    });
  time_t par_time1 = time(NULL);
  time_t par_timed = par_time1 - par_time0;

  assert(seq_solution == *par_solution);

  printf("Par. Solution: %d\n", *par_solution);
  printf("Par. Processor Time: %ld seconds\n", par_timed);
  DELETE(par_solution);

  int *hb_solution = NEW(int);
  *hb_solution = 0;
  time_t hb_time0 = time(NULL);
  root_interval(^(point_t *end) {
      hb_fibonacci(end, n, hb_solution);
    });
  time_t hb_time1 = time(NULL);
  time_t hb_timed = hb_time1 - hb_time0;

  assert(seq_solution == *hb_solution);

  printf("Par. Solution (HB): %d\n", *hb_solution);
  printf("Par. Processor Time (HB): %ld seconds\n", hb_timed);
  DELETE(hb_solution);

  // printf("Par/Seq Ratio: %.3f\n", (1.0 * par_timed) / seq_timed);

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

int parallel_fibonacci(int n) 
{
  if (n < THRESHOLD) {
    return sequential_fibonacci(n);
  }
  else {
    // Note: Due to subinterval, we know that the stack frame
    // will stick around :)
    int results[2];
    int *resultptr = results;
    subinterval(^(point_t *end) {
	interval(end, ^(point_t *_) {
	    resultptr[0] = parallel_fibonacci(n - 1);
	  });
	interval(end, ^(point_t *_) {
	    resultptr[1] = parallel_fibonacci(n - 2);                                       
	  });
      });
    return results[0] + results[1];
  }
}

interval_t hb_fibonacci(point_t *bound, int n, int *result) 
{
  interval_t i_n;
  if(n < 10) {
    i_n = interval(bound, ^(point_t *_) {
	*result = sequential_fibonacci(n);
      });
  } else {
    int *results = (int*)malloc(sizeof(int) * 2);
    interval_t i_nm1 = hb_fibonacci(bound, n - 1, results + 0);
    interval_t i_nm2 = hb_fibonacci(bound, n - 2, results + 1);
    i_n = interval(bound, ^(point_t *_) {
	*result = results[0] + results[1];
	free(results);
      });
    interval_add_hb(i_nm1.end, i_n.start);
    interval_add_hb(i_nm2.end, i_n.start);
  }
  interval_schedule();        
  return i_n;
}
