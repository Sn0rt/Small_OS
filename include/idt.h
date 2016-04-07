#ifndef INCLUDE_IDT_H_
#define INCLUDE_IDT_H_

#include "types.h"

void init_idt();

typedef
struct idt_entry_t {
  uint16_t base_low;           /* 中断处理函数地址0-15位*/
  uint16_t sel;               /* 目标代码描述符选择子 */
  uint8_t always0;            /* 置为0 */
  uint8_t flags;             /* 标志位 */
  uint16_t base_high;          /*  中断处理函数地址16-31位*/
}__attribute__((packed)) idt_entry_t;

typedef
struct idt_ptr_t {
  uint16_t limit;             /* 限长 */
  uint32_t base;              /* 基址 */
}__attribute__((packed)) idt_ptr_t;

typedef
struct pt_regs_t {
  uint32_t ds;                /* 用于保护用户数据段描述符 */
  uint32_t edi;               /* 从edi到eax有pusha指令压入 */
  uint32_t esi;
  uint32_t ebp;
  uint32_t esp;
  uint32_t ebx;
  uint32_t edx;
  uint32_t ecx;
  uint32_t eax;
  uint32_t int_no;            /* 中断号 */
  uint32_t err_code;          /* 错误代码有中断错误代码的 */
  uint32_t eip;               /* 以下有处理器自动压入 */
  uint32_t cs;
  uint32_t eflags;
  uint32_t useresp;
  uint32_t ss;
} pt_regs;

/* 中断处理函数指针 */
typedef void (*interrupt_handler_t)(pt_regs *);

/* 注册中断处理函数 */
void register_interrupt_handler(uint8_t n, interrupt_handler_t h);

/* 调用中断处理程序 */
void isr_handler(pt_regs *regs);

/* 声明中断处理程序0~19属于cpu和异常中断 */
/* ISR中断服务程序: interrupt service routing */

void isr0();                    /* 0 #DE 除0异常 */
void isr1();                    /* 1 #DB 调试异常 */
void isr2();                    /* 2 NMI */
void isr3();                    /* 3 BP断点异常  */
void isr4();                    /* 4 #OF 溢出 */
void isr5();                    /* 5 #BR 对数组的引用超过边界 */
void isr6();                    /* 6 #UD 无效或未定义的操作码 */
void isr7();                    /* 7 #NM 设备不可用无数学协处理器 */
void isr8();                    /* 8 #DF 双重故障错误代码 */
void isr9();                    /* 9 协处理器跨段操作 */
void isr10();                   /* 10 #TS 无效tss有错误代码 */
void isr11();                   /* 11 #NP 段不存在有错误的代码 */
void isr12();                   /* 12 #SS 栈错误有错误的代码 */
void isr13();                   /* 13 #GP 常规保护有错误的代码 */
void isr14();                   /* 14 #PF 页故障有错误的代码 */
void isr15();                   /* 15 CPU 保留 */
void isr16();                   /* 16 #MF 浮点处理单元错误 */
void isr17();                   /* 17 #AC 对齐检查 */
void isr18();                   /* 18 #MC 机器检查 */
void isr19();                   /* 19 #XM SIMD单指令 */

/* intel 保留 */
void isr20();
void isr21();
void isr22();
void isr23();
void isr24();
void isr25();
void isr26();
void isr27();
void isr28();
void isr29();
void isr30();
void isr31();

/* user define isr */
void isr255();

/* IRQ处理函数 */
void irq_handler(pt_regs *regs);

/* 定义IQR */
#define IRQ0 32                 /* timer */
#define IRQ1 33                 /* keryboard */
#define IRQ2 34                 /* 与IRQ9相连,mpu-401DM使用 */
#define IRQ3 33                 /* 串口设备 */
#define IRQ4 36                 /* 串口设备 */
#define IRQ5 37                 /* 建议声卡使用 */
#define IRQ6 38                 /* 软驱传输控制器 */
#define IRQ7 39                 /* 打印机传输控制器使用 */
#define IRQ8 40                 /* 即使时钟 */
#define IRQ9 41                 /* 有IRQ2相连 */
#define IRQ10 42                /* 建议网卡使用 */
#define IRQ11 43                /* 建议AGP显卡使用 */
#define IRQ12 44                /* 建议PS/2鼠标 */
#define IRQ13 45                /* 协处理器 */
#define IRQ14 46                /* IDE0传输 */
#define IRQ15 47                /* IDE1传输 */

/* 声明irq函数 */
void irq0();
void irq1();
void irq2();
void irq3();
void irq4();
void irq5();
void irq6();
void irq7();
void irq8();
void irq9();
void irq10();
void irq11();
void irq12();
void irq13();
void irq14();
void irq15();

#endif
