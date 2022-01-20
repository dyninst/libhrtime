#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <hrtime.h>

int
main(int argc, char *argv[])
{
    hrtime_t current;
    struct hrtime_struct *hr;
    int error;

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

    if (hr->has_ustime)
    {
        while (1)
        {
	    get_hrtime(hr, &current);
            printf("get_hrtime:  %10lld\n", current);
    
	    get_hrvtime(hr, &current);
            printf("get_hrvtime: %10lld\n", current);
    
	    get_hrstime(hr, &current);
            printf("get_hrstime: %10lld\n", current);
    
	    get_hrutime(hr, &current);
            printf("get_hrutime: %10lld\n", current);
        }
    }
    else
    {
        while (1)
        {
	    get_hrtime(hr, &current);
            printf("get_hrtime:  %10lld\n", current);
    
	    get_hrvtime(hr, &current);
            printf("get_hrvtime: %10lld\n", current);
        }
    }
    
    free_hrtime_struct(hr);

    return 0;
}
