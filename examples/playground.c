#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "interval.h"
#include "atomic.h"
#include "internal.h"

void no_bounds();
void nested();
void hb();
void schedule_before_hb();
void set_bounds();
void worker_hb_with_locks();

int main(int argc, char *argv[])
{
	printf("Intervals playground\n\n");

	no_bounds();
	nested();
	hb();
	schedule_before_hb();
	set_bounds();
	worker_hb_with_locks();

	return 0;
}

void no_bounds()
{
	printf("Intervals: No bounds\n");
	root_interval(^(point_t *end) {
			interval_t interval1 = interval(NULL, ^(point_t *_) {
					printf("interval 1\n");
				});
			interval_t interval2 = interval(NULL, ^(point_t *_) {
					printf("interval 2\n");
				});
			interval_t interval3 = interval(NULL, ^(point_t *_) {
					printf("interval 3\n");
				});
			interval_t interval4 = interval(NULL, ^(point_t *_) {
					printf("interval 4\n");
				});
			interval_t interval5 = interval(NULL, ^(point_t *_) {
					printf("interval 5\n");
				});
		});
	printf("\n");
}

void nested()
{
	printf("Intervals: Nested\n");
	root_interval(^(point_t *end) {
			interval_t interval1 = interval(NULL, ^(point_t *_) {
					printf("interval 1\n");
					interval_t interval2 = interval(NULL, ^(point_t *_) {
							printf("interval 2\n");
							interval_t interval3 = interval(NULL, ^(point_t *_) {
									printf("interval 3\n");
									interval_t interval4 = interval(NULL, ^(point_t *_) {
											printf("interval 4\n");

											interval_t interval5 = interval(NULL, ^(point_t *_) {
													printf("interval 5\n");
												});
										});
								});
						});
				});
		});
	printf("\n");
}

void schedule_before_hb()
{
	printf("Intervals: Schedule before HB (interval_add_hb())\n");
	root_interval(^(point_t *end) {
			interval_t interval1 = interval(NULL, ^(point_t *_) {
					printf("interval 1\n");
				});
			interval_t interval2 = interval(NULL, ^(point_t *_) {
					printf("interval 2\n");
				});
			interval_t interval3 = interval(NULL, ^(point_t *_) {
					printf("interval 3\n");
				});
			interval_t interval4 = interval(NULL, ^(point_t *_) {
					printf("interval 4\n");
				});
			interval_t interval5 = interval(NULL, ^(point_t *_) {
					printf("interval 5\n");
				});

			interval_schedule();

			interval_add_hb(interval1.end, interval2.start);
			interval_add_hb(interval2.end, interval3.start);
			interval_add_hb(interval3.end, interval4.start);
			interval_add_hb(interval4.end, interval5.start);
		});
	printf("\n");
}

void hb()
{
	printf("Intervals: HB (interval_add_hb())\n");
	root_interval(^(point_t *end) {
			interval_t interval1 = interval(NULL, ^(point_t *_) {
					printf("interval 1\n");
				});
			interval_t interval2 = interval(NULL, ^(point_t *_) {
					printf("interval 2\n");
				});
			interval_t interval3 = interval(NULL, ^(point_t *_) {
					printf("interval 3\n");
				});
			interval_t interval4 = interval(NULL, ^(point_t *_) {
					printf("interval 4\n");
				});
			interval_t interval5 = interval(NULL, ^(point_t *_) {
					printf("interval 5\n");
				});
			interval_add_hb(interval1.end, interval2.start);
			interval_add_hb(interval2.end, interval3.start);
			interval_add_hb(interval3.end, interval4.start);
			interval_add_hb(interval4.end, interval5.start);
		});
	printf("\n");
}

void set_bounds()
{
	printf("Intervals: Explicitly set bounds\n");
	root_interval(^(point_t *end) {
			interval_t interval5 = interval(NULL, ^(point_t *_) {
					printf("interval 5\n");
				});
			interval_t interval4 = interval(interval5.start, ^(point_t *_) {
					printf("interval 4\n");
				});
			interval_t interval3 = interval(interval4.start, ^(point_t *_) {
					printf("interval 3\n");
				});
			interval_t interval2 = interval(interval3.start, ^(point_t *_) {
					printf("interval 2\n");
				});
			interval_t interval1 = interval(interval2.start, ^(point_t *_) {
					printf("interval 1\n");
				});

			interval_schedule();
		});
	printf("\n");
}

void worker_hb_with_locks()
{
	printf("Intervals: Workers with locks and join\n");
	guard_t* guard = create_guard();
	root_interval(^(point_t *end) {
			interval_t afterJoin = interval(NULL, ^(point_t *_) {
					printf("after join\n");
				});

			for (int i = 0; i < 5; i++) {
				interval_t worker = interval(NULL, ^(point_t *_) {
						printf("worker %d\n", i);
						sleep(1);
						printf("worker %d\n", i);
					});
				interval_add_hb(worker.end, afterJoin.start);
				interval_add_lock(worker.start, guard);
			}
		});
	printf("\n");
}
