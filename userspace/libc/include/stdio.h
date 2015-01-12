// Projectname: SWEB
// Simple operating system for educational purposes
//
// Copyright (C) 2005  Andreas Niederl
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef stdio_h___
#define stdio_h___

// stdarg.h is taken from gcc
#include <stdarg.h>

#include "unistd.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * Size of <stdio.h> buffers
 *
 */
#define BUFSIZ 4096


/**
 * Input/output fully buffered
 *
 */
#define _IOFBF 0x0000

/**
 * Input/output line buffered
 *
 */
#define _IOLBF 0x0001

/**
 * Input/output unbuffered
 *
 */
#define _IONBF 0x0002


/**
 * Maximum size of character array to hold ctermid() output
 *
 */
#define L_ctermid 64

/**
 * Maximum size of character array to hold tmpnam() output
 *
 */
#define L_tmpnam 64


/**
 * Set file offset to offset, defined for lseek() and fcntl()
 *
 */
#define SEEK_SET 0x0000

/**
 * Set file offset to current + offset, defined for lseek() and fcntl()
 *
 */
#define SEEK_CUR 0x0001

/**
 * Set file offset to EOF + offset, defined for lseek() and fcntl()
 *
 */
#define SEEK_END 0x0002


/**
 * Maximum size in bytes of the longest filename string that the implementation
 * guarantees can be opened.
 *
 */
#define FILENAME_MAX 256

/**
 * Number of streams which the implementation guarantees can be opened
 * simultaneously. The value is at least eight.
 *
 */
#define FOPEN_MAX 8

/**
 * Minimum number of unique filenames generated by tmpnam(). Maximum number of
 * times an application can call tmpnam() reliably. The value of TMP_MAX is at
 * least 25.
 *
 */
#define TMP_MAX 25


/**
 * End-of-file return value
 *
 */
#define EOF -1

/**
 * NULL pointer constant
 *
 */
#define NULL 0


/**
 * Default directory prefix for tempnam()
 *
 */
#define P_tmpdir /tmp


/**
 * A non-array type containing all information needed to specify uniquely
 * every position within a file.
 *
 */
typedef off_t fpos_t;

/**
 * Renames a file, moving it between directories if required.
 *
 * @param old_path The old pathname
 * @param new_path The new pathname
 * @return 0 on success, -1 otherwise and errno is set appropriately
 *
 */
extern int rename(const char *old_path, const char *new_path);

/**
 * Equivalent to getc(stdin).
 *
 * @return The read character on success, EOF otherwise and errno is set\
 appropriately
 *
 */
extern int getchar();

/**
 * Reads a line from stdin and stores it in the string pointed to by the
 * argument.
 * Reading is terminated by a newline, EOF which are both replaced by '\0' or
 * when the buffer is full.
 *
 * @param input_buffer The buffer where the input is stored
 * @param buffer_size The size of the buffer
 * @return A pointer to the input_string on success, NULL otherwise
 *
 */
extern char *gets(char *input_buffer, size_t buffer_size);

/**
 * Equivalent to putc(character, stdout).
 *
 * @param character The character for writing
 * @return The character written as unsigned char cast to int or EOF on error
 *
 */
extern int putchar(int character);

/**
 * Writes the given string followed by a newline to stdout.
 *
 * @param output_string The string for writing
 * @return A non-negative number on success or EOF on error
 *
 */
extern int puts(const char *output_string);


/**
 * Writes output to stdout.
 * A detailed description of the format is given in the
 * 'Linux Programmer's Manual'.
 *
 * @param format A string containing the output format, followed by an\
 argument list containing different variables for output
 * @return The number of characters printed or the number of characters that\
 would have been printed if the output was truncated, a negative\
 value is returned on failure
 *
 */
extern int printf(const char *format, ...);

/**
 * Prints an error message on the standard error output describing the last
 * error encountered during a call to a system or library function.
 * This function first prints the given error message string, if it is not
 * NULL and has a length greater zero, followed by a colon and a blank.
 * After that the message corresponding to the last error is printed
 * followed by a new-line.
 * It is useful to include the name of the function that failed in the
 * argument string.
 *
 * The last error number is stored in the external variable errno which
 * indexes the global error list sys_errlist[]. By accessing this list with
 * errno as index, the message for the error can be obtained.
 * The largest index for sys_errlist[] is the value of the external variable
 * sys_nerr - 1.
 *
 * The variable errno has undefined state if the call to a function succeeded.
 * If a failing call is not immediately followed by a call to perror() then
 * the value of errno should be saved.
 *
 * @param error_msg Additional error message
 *
 */
extern void perror(const char *error_msg);

/**
 * Reads input from stdin according to the given format and
 * assigns read values to the given variables.
 * A detailed description of the format is given in the
 * 'Linux Programmer's Manual'.
 *
 * @param format A string containing the input format, followed by an\
 argument list of variables for assignment
 * @return The number of input items assigned, zero indicates that no input\
 items were assigned while input was available, EOF if failure (e.g.\
 end-of-file) occurs before any items have been read
 *
 */
extern int scanf(const char *format, ...);

#ifdef __cplusplus
}
#endif

#endif // stdio_h___


