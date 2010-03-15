#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "interval.h"
#include "atomic.h"
#include "internal.h"

int array[23];

void set(int index, int value);

int main(int argc, char *argv[])
{
	printf("Fork/Join with Intervals\n\n");

	root_interval(^(point_t *end) {
			for(int i = 0; i < 22; i++) {
				interval(NULL, ^(point_t *_) {
						set(i, i);
					});
			}
		});

	// At this point, all of those intervals should have finished!
	array[22] = -1;

	// Check that values got set
	for(int i = 0; i < 22; i++) {
		assert(array[i] == i);
	}

	// Last array element has value '-1'
	assert(array[22] == -1);

	printf("\nDone.\n");

	return 0;
}

void set(int index, int value)
{
	array[index] = value;
	printf("array[%i] = %i\n", index, value);
}
