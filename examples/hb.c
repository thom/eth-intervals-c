#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "interval.h"
#include "atomic.h"
#include "internal.h"

int main(int argc, char *argv[])
{
  printf("Intervals\n\n");

  root_interval(^(point_t *end) {
      interval_t a = interval(end, ^(point_t *_) {
	  printf("Interval a\n");
	});

      interval_t b = interval(end, ^(point_t *_) {
	  printf("Interval b\n");
	});

      interval_t c = interval(end, ^(point_t *_) {
	  printf("Interval c\n");
	});

      interval_add_hb(b.end, c.start);
      interval_schedule();
    });

  printf("\nDone.\n");

  return 0;
}
