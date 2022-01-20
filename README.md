# This project is no longer maintained


##libhrtime

libhrtime, Version 0.6.1
High-Resolution Process Timing for the Linux Kernel
Copyright (C) 2000, Nick Rasmussen <nick@jive.org>
Location: http://www.paradyn.org/projects/legacy/libhrtime/

This patch adds very low-overhead access to high-resolution process virtual
time and, optionally, high-resolution virutalized user and system time.
The timers are based on the CPU timestamp counter and can be read at
memory access speeds.  Low overhead access to high-resolution process time
is critical many profiling and benchmarking applications.

While other systems have offered access to high-resolution process time,
they have required access through a system call interface.

Our approach uses an extra per-pid entry, /proc/PID/hrtime, that contains
timing values; these values can be mmapped into a user's address space.
For convienience, a library is also provided that performs the mmaping
and timer querying work for you.

These routines work both for a process timing itself and a process timing
another process.

The library interface to get high-resolution timing information is:

```
int get_hrtime_struct(pid_t pid, volatile struct hrtime_struct **dest);
  Map the given timing page.

int free_hrtime_struct(volatile struct hrtime_struct *hr);
  Unmap the given timing page.

void get_hrtime(volatile struct hrtime_struct *hr, hrtime_t *dest);
  Get the total wall time in ticks.

void get_hrvtime(volatile struct hrtime_struct *hr, hrtime_t *dest);
  Get the total virtual time in ticks

void get_hrutime(volatile struct hrtime_struct *hr, hrtime_t *dest);
  Get the total virtualized user time in ticks (only if CONFIG_HRUSTIME was
  enabled)

void get_hrstime(volatile struct hrtime_struct *hr, hrtime_t *dest);
  Get the total virtualized system time in ticks (only if CONFIG_HRUSTIME was
  enabled)
```

###TODO/BUGS:

- Run some test cases to see what the cumulative slowdown (in cycles per syscall)
when CONFIG_HRUSTIME is enabled.

- Compute the timestamp difference between multiple CPUs in SMP boxes, and
do all hrtime (wall time) operations with reference to CPU 0.

- Add support for other architectures.

- Figure out what to do with threaded programs.

###CREDITS:

This work was done for the Paradyn Parallel Performance Tools project
at the University of Wisconsin (http://www.cs.wisc.edu/paradyn/) and
was initially inspired by the vtimer patch by dadkins@mit.edu and
bsong@supertech.lcs.mit.edu.

###LICENSE:

libhrtime and the hrtime kernel patches can be considered public domain.

