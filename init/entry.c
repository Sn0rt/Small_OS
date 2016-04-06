#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"

int kern_entry()
{
    init_debug();
    init_gdt();
    init_idt();
    console_clear();
    printk_color(rc_black, rc_green, "Hello Small OS!\n");
//    asm volatile("int $0x01");
//    asm volatile("int $0x02");
    init_timer(200);
    asm volatile("sti");
    return 0;
}
