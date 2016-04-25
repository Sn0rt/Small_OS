#include "console.h"
#include "common.h"
#include "vmm.h"

/* 定义80*25标准console */
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

/* 显存位置 */
static uint16_t *void_memory = (uint16_t *)(0xB8000 + PAGE_OFFSET) ;
static uint8_t cursor_x = 0;
static uint8_t cursor_y = 0;

static void move_cursor()
{
    uint16_t cursor_where = cursor_y * VGA_WIDTH + cursor_x;
    outb(0x3D4, 14);
    outb(0x3D5, cursor_where >> 8);
    outb(0x3D4, 15);
    outb(0x3D5, cursor_where);
}

static void scroll()
{
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);
    if (cursor_y >= VGA_HEIGHT) {
        for (int i = 0;  i < 24 * VGA_WIDTH; i++) {
            void_memory[i] = void_memory[i + VGA_WIDTH];
        }
        for (int i = 24 * VGA_WIDTH; i < VGA_HEIGHT * VGA_WIDTH; i++) {
            void_memory[i] = blank;
        }
        cursor_y = 24;
    }
}

void console_clear()
{
    uint8_t attribute_byte = (0 << 4) | (15 & 0x0F);
    uint16_t blank = 0x20 | (attribute_byte << 8);
    for (int i = 0; i < VGA_WIDTH * VGA_HEIGHT; i++) {
        void_memory[i] = blank;
    }
    cursor_x = 0;
    cursor_y = 0;
    move_cursor();
}


void console_putc_color(char c, real_color_t back, real_color_t fore)
{
    uint8_t back_color = (uint8_t)back;
    uint8_t fore_color = (uint8_t)fore;

    uint8_t attribute_byte = (back_color << 4) | (fore_color & 0x0F);
    uint16_t attribute = attribute_byte << 8;

    if (c == 0x08 && cursor_x) {
        cursor_x--;
    } else if (c == 0x09) {
        cursor_x = (cursor_x+8) & ~(8-1);
    } else if (c == '\r') {
        cursor_x = 0;
    } else if (c == '\n') {
        cursor_x = 0;
        cursor_y++;
    } else if (c >= ' ') {
        void_memory[cursor_y * VGA_WIDTH + cursor_x] = c | attribute;
        cursor_x++;
    }
    if (cursor_x >= VGA_WIDTH) {
        cursor_x = 0;
        cursor_y++;
    }
    scroll();
    move_cursor();
}

void console_write(char *cstr)
{
    while (*cstr) {
        console_putc_color(*cstr++, rc_black, rc_white);
    }
}

void console_write_color(char *cstr, real_color_t back, real_color_t fore)
{
    while (*cstr) {
        console_putc_color(*cstr++, back, fore);
    }
}
