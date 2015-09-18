#include "common.h"

//the port write a chart
inline void outb(uint16_t port, uint8_t value)
{
    asm volatile ("outb %1, %0" : : "dN"(port), "a" (value));
}

//the port read a chart
inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0": "=a" (ret): "dN"(port));
    return 0;
}

//the port read a word
inline uint16_t inw(uint16_t port)
{
    uint16_t ret;
    asm volatile ("inw %1, %0" : "=a" (ret) : "dN"(port));
    return ret;
}
