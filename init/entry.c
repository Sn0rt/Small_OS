#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "pmm.h"

int kern_entry()
{
    init_debug();
    init_gdt();
    init_idt();

    console_clear();
    printk_color(rc_black, rc_green, "Hello Small OS!\n");
    asm volatile("int $0x01");
    asm volatile("int $0x02");
    init_timer(200);
//    asm volatile("sti");
    printk("kernel in memory start: 0x%08X\n", kern_start);
    printk("kernel in memory end: 0x%08X\n", kern_end);
    printk("kernel in memory used: %dKB\n", (kern_end - kern_start + 1023) / 1024);
    show_memory_map();
    return 0;
}
