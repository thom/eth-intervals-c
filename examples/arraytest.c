#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "interval.h"
#include "atomic.h"
#include "internal.h"

typedef void(^ArrayBlock)(int[], int, int);

void set(int array[], int index, int value) {
  array[index] = value;
  printf("array[%i] = %i\n", index, value);
}

int main(int argc, char *argv[]) {
  int array[2] = { 1, 2 };

  ArrayBlock ab = ^ void (int a[], int i, int v) {
    set(a, i, v);
  };

  ab(array, 1, 2);
  ab(array, 1, 4);

  // root_interval(^(point_t *end) {
  //   set(array, 1, 2);
  //   set(array, 1, 4);
  //  });

  printf("%d, %d\n", array[0], array[1]);

  return 0;
}
