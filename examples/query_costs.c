#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <hrtime.h>
#include <sys/times.h>

#define NUM_TIMES 200

#define benchmark_general(X) do_benchmark_general(X, #X)
#define benchmark_self(X)    do_benchmark_self(X, #X)

static struct hrtime_struct *hr = 0;
static long timing_cost = 0;

void
do_benchmark_general(void(*query_func)(struct hrtime_struct *, hrtime_t *),
                     const char *name)
{
    hrtime_t current;
    hrtime_t old;
    hrtime_t tmp;

    long query_total   = 0;
    long query_avg     = 0;

    int i;

    for (i = 0; i < NUM_TIMES; ++i)
    {
        get_hrvtime(hr, &old);
        query_func(hr, &tmp);
        get_hrvtime(hr, &current); 
        tmp = current - old;
        query_total += tmp;
    }

    query_avg = query_total / NUM_TIMES;

    printf("%s:\t\tcost + query is %ld (%ld for %d)\n", name,
           query_avg, query_total, NUM_TIMES);

    printf("\t\t\t...which means that the average cycles/query is %ld\n\n",
           query_avg - timing_cost);
}

void
do_benchmark_self(void(*query_func)(hrtime_t *), const char *name)
{
    hrtime_t current;
    hrtime_t old;
    hrtime_t tmp;

    long query_total   = 0;
    long query_avg     = 0;

    int i;

    for (i = 0; i < NUM_TIMES; ++i)
    {
        get_hrvtime(hr, &old);
        query_func(&tmp);
        get_hrvtime(hr, &current); 
        tmp = current - old;
        query_total += tmp;
    }

    query_avg = query_total / NUM_TIMES;

    printf("%s:\tcost + query is %ld (%ld for %d)\n", name,
           query_avg, query_total, NUM_TIMES);

    printf("\t\t\t...which means that the average cycles/query is %ld\n\n",
           query_avg - timing_cost);
}

int
main(int argc, char *argv[])
{
    hrtime_t current;
    hrtime_t old;

    long query_total   = 0;
    int error;
    int i;

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

    /* time just the query cost */
    query_total = 0;
    for (i = 0; i < NUM_TIMES; ++i)
    {
	get_hrvtime(hr, &old);
	get_hrvtime(hr, &current);
	tmp = current - old;
        query_total += tmp;
    }
    timing_cost = query_total / NUM_TIMES;

    printf("timing overhead for measuring functions is approximately "
           "%ld (%ld for %d)\n", timing_cost, query_total, NUM_TIMES);

    benchmark_general(get_hrtime);
    benchmark_general(get_hrvtime);
    benchmark_general(get_hrutime);
    benchmark_general(get_hrstime);

    benchmark_self(get_hrtime_self);
    benchmark_self(get_hrvtime_self);
    benchmark_self(get_hrutime_self);
    benchmark_self(get_hrstime_self);

    free_hrtime_struct(hr);
    return 0;
}
