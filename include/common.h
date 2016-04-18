#ifndef INCLUDE_COMMON_H_
#define INCLUDE_COMMON_H_
#include "types.h"

// out
void outb (uint16_t port, uint8_t value);

// in
uint8_t inb(uint16_t port);

// in a word
uint16_t inw(uint16_t prot);

// enable interrupt
void enable_intr();

// disable interrupt
void disable_intr();

#endif
