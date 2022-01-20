#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <hrtime.h>

int
main(int argc, char *argv[])
{
    hrtime_t current;
    struct hrtime_struct *hr;
    int error, i, j;
    pid_t pid;

    pid = fork();

    if (pid == 0)
    {
        /* child process */
        for (j = 0; j < 10; j++)
        {
            /* burn some vtime :) */
            for (i = 0; i < 100000; ++i) {}
            sleep(1);
        }
        /* make sure exit doesn't blow up */
        exit(0);
    }

    error = hrtime_init();
    if (error < 0)
    {
        printf("Error: %s\n", strerror(error));
	exit(1);
    }

    error = get_hrtime_struct(pid, &hr);
    if (error < 0)
    {
        printf("Error: %s\n", strerror(error));
	exit(1);
    }

    printf("hr is 0x%08x\n", (unsigned int) hr);

    while (1)
    {
	get_hrtime(hr, &current);
        printf("get_hrtime(mmap):  %10lld\n", current);

	get_hrvtime(hr, &current);
        printf("get_hrvtime(mmap): %10lld\n", current);

	get_hrstime(hr, &current);
        printf("get_hrstime(mmap): %10lld\n", current);

	get_hrutime(hr, &current);
        printf("get_hrutime(mmap): %10lld\n", current);
    }

    free_hrtime_struct(hr);

    return 0;
}
