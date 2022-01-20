lib_LTLIBRARIES		= libhrtime.la
include_HEADERS		= hrtime.h hrtime_shadow.h
libhrtime_la_SOURCES	= hrtime.c
libhrtime_la_LDFLAGS	= -release @VERSION@
DISTCLEANFILES		= hrtime_shadow.h
EXTRA_DIST		= hrtime_shadow.h.top hrtime_shadow.h.bottom include_hrtime.h

hrtime.c: hrtime.h

hrtime.h: hrtime_shadow.h

hrtime_shadow.h: hrtime_shadow.h.top hrtime_shadow.h.bottom include_hrtime.h
	-rm -f $@
	cp $(srcdir)/hrtime_shadow.h.top $@
	$(CPP) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(srcdir)/include_hrtime.h >> $@
	cat $(srcdir)/hrtime_shadow.h.bottom >> $@

