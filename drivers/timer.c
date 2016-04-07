#include "timer.h"
#include "debug.h"
#include "common.h"
#include "idt.h"

void timer_callback(pt_regs *regs)
{
  static uint32_t tick = 0;
  printk_color(rc_black, rc_red, "tick: %d\n", tick++);
}

void init_timer(uint32_t frequency)
{
  // 注册时间相关的处理函数
  register_interrupt_handler(IRQ0, timer_callback);

  // intel 8253/8254 芯片PIT/I端口地址范围040h~43h
  // 输入频率1193180 frequency 即每秒中断次数
  uint32_t divisor = 1193180 / frequency;

  // D7 D6 D5 D4 D3 D2 D1 D0
  // 0  0  1  1  0  1  1  0   0x36
  // 设置8253/8254芯片工作在模式3下面
  outb(0x43, 0x36);

  // 拆分低字节和高字节
  uint8_t low = (uint8_t)(divisor & 0xff);
  uint8_t high = (uint8_t)((divisor >> 8) & 0xff);

  // 分别写入
  outb(0x40, low);
  outb(0x40, high);
}
