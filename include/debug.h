#ifndef INCLUDE_DEBUG_H_
#define INCLUDE_DEBUG_H_

#include "console.h"
#include "vargs.h"
#include "elf.h"

#define assert(x, info)                         \
    do {                                        \
        if (!(x)) {                             \
        panic(info);                            \
        }                                       \
    } while(0)

#define static_assert(x)                        \
    switch (x) {case 0: case(x): ;}             \

extern void init_debug();

extern void panic(const char *msg);

extern void print_cur_status();

extern void printk(const char *format, ...);

extern void printk_color(real_color_t back, real_color_t fore, const char *format, ...);
#endif
