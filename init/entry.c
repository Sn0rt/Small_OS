#include "console.h"
#include "debug.h"

int kern_entry()
nn{
    init_debug();
    console_clear();
    printk_color(rc_black, rc_green, "Hello Small OS!\n");
    panic("test");
    return 0;
}
