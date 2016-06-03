#include "debug.h"
#include "printk.h"

static void print_stack_trace();
static elf_t kernel_elf;

void init_debug()
{
    kernel_elf = elf_from_multiboot(glb_mboot_ptr);
}

void print_cur_status()
{
    static int round = 0;
    uint16_t reg0, reg1, reg2, reg3;

    asm volatile ( "mov %%cs, %0;"
                   "mov %%ds, %1;"
                   "mov %%es, %2;"
                   "mov %%ss, %3;"
                   : "=m"(reg0),  "=m"(reg1),  "=m"(reg2),  "=m"(reg3));
    printk("%d: @ring %d\n", round, reg0 & 0x3);
    printk("%d: cs = %x\n", round, reg0);
    printk("%d: ds = %x\n", round, reg1);
    printk("%d: es = %x\n", round, reg2);
    printk("%d: ss = %x\n", round, reg3);
    ++round;
}

void panic(const char *msg)
{
    printk("*** SYSTEM PAINC :%s\n", msg);
    print_stack_trace();
    printk("***\n");
    while(1);
}

void print_stack_trace()
{
    uint32_t *ebp,*eip;

    asm volatile ("mov %%ebp, %0"
                  : "=r"(ebp));
    while(ebp) {
        eip = ebp + 1;
        printk(" [0x%x] %s\n", *eip, elf_lookup_symbol(*eip, &kernel_elf));
        ebp = (uint32_t *)*ebp;
    }
}
