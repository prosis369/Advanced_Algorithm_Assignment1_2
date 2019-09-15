#include "splay_tree_imp.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define BENCHMARK_COUNT 100


// function to start a nanosecond-resolution timer
struct timespec timer_start(){
	struct timespec start_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time);
	return start_time;
}

// function to end a timer, returning nanoseconds elapsed as a long
long timer_end(struct timespec start_time){
	struct timespec end_time;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	long diffInNanos = (end_time.tv_sec - start_time.tv_sec) * (long)1e9 + (end_time.tv_nsec - start_time.tv_nsec);
	return diffInNanos;
}

int main() {

    void* dictionary = make_new_dictionary();
    long total_time = 0;
    for(int i=1; i<=BENCHMARK_COUNT; ++i) {
        struct timespec vartime = timer_start();
        if(i%2) {
            int key = random()%BENCHMARK_COUNT;
            int value = random()%BENCHMARK_COUNT;
            insert(dictionary, key, value);
            // preOrder(dictionary->root);
            // printf("\ninserted: %d, %d\n", key, value);
            // printf("------------\n");
        }
        else {
            // int f = random()%BENCHMARK_COUNT;
            // printf("find: %d\n", f);
            // printf("%d\n ", find(dictionary, f));
            find(dictionary, random()%BENCHMARK_COUNT);
            // printf("------------\n");
        }
        long time_elapsed_nanos = timer_end(vartime);
        total_time = total_time + time_elapsed_nanos;
        printf("%ld\n", time_elapsed_nanos);
    }
    long avg_time = total_time/BENCHMARK_COUNT;
    printf("-------\n");
    printf("%ld\n", total_time);
    printf("%ld\n", avg_time);
    printf("%d\n", count_copy);
}
