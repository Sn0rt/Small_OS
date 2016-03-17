#ifndef INCLUDE_CONSOLE_H_
#define INCLUDE_CONSOLE_H_

#include "common.h"

//The constat of color
typedef enum real_color {
    rc_black = 0,
    rc_bule = 1,
    rc_green =  2,
    rc_cyan = 3,
    rc_red = 4,
    rc_magenta = 5,
    rc_brown = 6,
    rc_light_grey = 7,
    rc_dark_grey = 8,
    rc_light_blue = 9,
    rc_light_green = 10,
    rc_light_cyan = 11,
    rc_light_red = 12,
    rc_light_magenta = 13,
    rc_light_brown = 14,
    rc_white = 15
}    real_color_t;

extern void move_cursor();

extern void console_clear();

extern void console_scroll();

extern void console_putc_color(char, real_color_t, real_color_t);

extern void console_write(char *);

extern void console_write_color(char *, real_color_t, real_color_t);

extern void console_write_hex(uint32_t, real_color_t, real_color_t);

extern void console_write_dec(uint32_t, real_color_t, real_color_t);

#endif
