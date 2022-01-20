#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <hrtime.h>
#include <sys/times.h>

#define NUM_TIMES 200

int
main(int argc, char *argv[])
{
    hrtime_t current;
    hrtime_t old;
    struct hrtime_struct *hr;
    int error;
    int i;

    long syscall_total = 0;
    long syscall_avg   = 0;
    long query_total   = 0;
    long query_avg     = 0;

    long min = 1000000;
    long tmp;

    error = hrtime_init();
    if (error < 0)
    {
        printf("Error: %s\n", strerror(error));
	exit(1);
    }

    error = get_hrtime_struct(0, &hr);
    if (error < 0)
    {
        printf("Error: %s\n", strerror(error));
	exit(1);
    }

    for (i = 0; i < NUM_TIMES; ++i)
    {
	struct tms t;
	get_hrvtime(hr, &old);
        times(&t);
	get_hrvtime(hr, &current);
	tmp = current - old;
        syscall_total += tmp;
        if (tmp < min) min = tmp;
    }

    free_hrtime_struct(hr);
  
    syscall_avg = syscall_total / NUM_TIMES;

    printf("syscall cost + query is %ld (%ld for %d)\n",
           syscall_avg, syscall_total, NUM_TIMES);

    printf("minimum time is %ld\n", min);

    /* now time just the query */
    query_total = 0;
    for (i = 0; i < NUM_TIMES; ++i)
    {
	get_hrvtime(hr, &old);
	get_hrvtime(hr, &current);
	tmp = current - old;
        query_total += tmp;
        if (tmp < min) min = tmp;
    }

    query_avg = query_total / NUM_TIMES;

    printf("query cost is approximately %ld (%ld for %d)\n",
           query_avg, query_total, NUM_TIMES);


    printf("...which means that the average syscall cost is %ld\n",
           syscall_avg - query_avg);

    return 0;
}
