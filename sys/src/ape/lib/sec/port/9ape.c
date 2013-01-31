/*
 * This file brings in support functions from Plan 9 libc and others
 * in order to provide a decent wrapper to libsec.
 */

#include "libc.h"

static void
_sysfatalimpl(char *fmt, va_list arg)
{
	char buf[1024];

	vseprint(buf, buf+sizeof(buf), fmt, arg);
	if(argv0)
		fprint(2, "%s: %s\n", argv0, buf);
	else
		fprint(2, "%s\n", buf);
	exits(buf);
}

void (*_sysfatal)(char *fmt, va_list arg) = _sysfatalimpl;

void
sysfatal(char *fmt, ...)
{
	va_list arg;

	va_start(arg, fmt);
	(*_sysfatal)(fmt, arg);
	va_end(arg);
}
