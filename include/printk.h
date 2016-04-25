#ifndef INCLUDE_PRINTK_H_
#define INCLUDE_PRINTK_H_

#include "console.h"
#include "string.h"
#include "vargs.h"
#include "kern_levels.h"

#define CONSOLE_LOGLEVEL_SILENT  0 /* Mum's the word */
#define CONSOLE_LOGLEVEL_MIN     1 /* Minimum loglevel we let people use */
#define CONSOLE_LOGLEVEL_QUIET   4 /* Shhh ..., when booted with "quiet" */
#define CONSOLE_LOGLEVEL_DEFAULT 7 /* anything MORE serious than KERN_DEBUG */
#define CONSOLE_LOGLEVEL_DEBUG  10 /* issue debug messages */
#define CONSOLE_LOGLEVEL_MOTORMOUTH 15  /* You can't shut this one up */

#define is_digit(c)	((c) >= '0' && (c) <= '9')

#define ZEROPAD		1	// pad with zero
#define SIGN	 	2   	// unsigned/signed long
#define PLUS    	4	// show plus
#define SPACE	  	8   	// space if plus
#define LEFT	 	16  	// left justified
#define SPECIAL		32  	// 0x
#define SMALL	  	64  	// use 'abcdef' instead of 'ABCDEF'
#define do_div(n,base) ({ \
		int __res; \
		__asm__("divl %4":"=a" (n),"=d" (__res):"0" (n),"1" (0),"r" (base)); \
		__res; })

extern void print_cur_status();

extern void printk(const char *format, ...);

extern void printk_color(real_color_t back, real_color_t fore, const char *format, ...);


#endif
