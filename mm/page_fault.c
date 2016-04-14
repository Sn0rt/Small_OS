#include "vmm.h"
#include "debug.h"

void page_fault(pt_regs *regs)
{
  uint32_t cr2;
  asm volatile("mov %%cr2, %0\n\t"
               : "=r" (cr2));
  printk("Page fault at 0x%x virtual faulting address 0x%x\n", regs->eip, cr2);
  printk("Error code: %x\n", regs->err_code);

  // bit 0 为0指页面不存在内存里面
  if (!(regs->err_code & 0x01)) {
    printk_color(rc_black, rc_light_red, "Because the page wasn't present\n");
  }

  // bit 1, 0表示读错误,1表示写错误
  if (regs->err_code & 0x02) {
    printk_color(rc_black, rc_light_red, "write error\n");
  } else {
    printk_color(rc_black, rc_light_red, "read error\n");
  }

  // bit 2, 0表示内核模式打断, 1表示用户模式打断.
  if (regs->err_code & 0x04) {
    printk_color(rc_black, rc_light_red, "In user mode\n");
  } else {
    printk_color(rc_black, rc_light_red, "In kernel mode\n");
  }

  // bit 3, 1表示错误是由保留位覆盖造成的
  if (regs->err_code & 0x8) {
    printk_color(rc_black, rc_light_red, "Reserved bits being overwritten\n");
  }

  if (regs->err_code & 0x10) {
    printk_color(rc_black, rc_light_red, "The fault occurred during an instruction fetch\n");
  }
  while(1);
}
