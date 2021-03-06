#ifndef KPRINTF_H__
#define KPRINTF_H__

#include "stdarg.h"
#include "types.h"
#include "debug.h"

/**
 * Standard kprintf. Usable like any other printf.
 * Outputs Text on the Console. It is intendet for
 * Kernel Debugging and therefore avoids using "new".
 * @param fmt Format String with standard Format Syntax
 * @param args Possible multibple variable for printf as specified in Format String.
 */
void kprintf ( const char *fmt, ... );

/**
 * Usable like any other printf.
 * kprintfd is a shorthand for kprintf_debug
 * Outputs Text on the Serial Debug Console. It is intendet for
 * Kernel Debugging and therefore avoids using "new".
 * @param fmt Format String with standard Format Syntax
 * @param args Possible multibple variable for printf as specified in Format String.
 */
void kprintfd ( const char *fmt, ... );
/**
 * Initializes the nosleep functionality and starts the flushing thread.
 */
void kprintf_init();

#endif
