#include "console.h"
#include "common.h"
#include "sched.h"
#include "task.h"
#include "heap.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "vmm.h"
#include "pmm.h"

// 内核初始化函数
void kern_init();

// 开启分页过后multiboot数据指针
multiboot_t *glb_mboot_ptr;

// 开启分页过后的内核栈
uint8_t kern_stack[STACK_SIZE] __attribute__((aligned(16)));

// 维护内核栈顶端
uint32_t kern_stack_top;

/* 内核使用的临时页表和页目录
 * 地址页对齐,内存0-640k肯定是空闲的
 */
__attribute__((section(".init.data"))) pgd_t *pgd_tmp = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low = (pgd_t *)0x2000;
__attribute__((section(".init.data"))) pgd_t *pte_high = (pgd_t *)0x3000;

// 内核入口
__attribute__((section(".init.text"))) void kern_entry()
{
  pgd_tmp[0] = (uint32_t)pte_low | PAGE_PRESENT | PAGE_WRITE;
  pgd_tmp[PGD_INDEX(PAGE_OFFSET)] = (uint32_t)pte_high | PAGE_PRESENT | PAGE_WRITE;

  /* 映射内核虚拟地址4MB到物理地址最前面4MB */
  for (int i = 0; i < 1024; i++) {
    pte_low[i] = (i << 12) | PAGE_WRITE | PAGE_PRESENT;
  }
  for (int i = 0; i < 1024; i++) {
    pte_high[i] = (i << 12) | PAGE_WRITE | PAGE_PRESENT;
  }

  /* 设置临时页表 */
  asm volatile ("mov %0, %%cr3\n\t"
                :
                :"r"(pgd_tmp));
  uint32_t cr0;

  /* 启用分页,将cr0的分页标志置为1 */
  asm volatile ("mov %%cr0, %0\n\t"
                : "=r" (cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0\n\t"
               :
               :"r" (cr0));

  /* 切换内核线程 */
  kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE);
  asm volatile ("mov %0, %%esp\n\t"
                "xor %%ebp, %%ebp\n\t"
                :
                :"r" (kern_stack_top));

  /* 更新全局multiboot指针 */
  glb_mboot_ptr = mboot_ptr_tmp + PAGE_OFFSET;

  /* 内核开始初始化 */
  kern_init();
}

// 内核线程A-B
// flag原始互斥量
int flag = 0;

int thread_B(void *arg)
{
  while(1) {
    if (flag == 1) {
      printk_color(rc_black, rc_green, "B");
      flag = 0;
    }
  }
  return 0;
}

int thread_A(void *arg)
{
  while (1) {
    if (flag == 0) {
      printk_color(rc_black, rc_red, "A");
      flag = 1;
    }
  }
}

// 内核初始化
void kern_init()
{
  init_debug();
  init_gdt();
  init_idt();

  console_clear();
  printk_color(rc_black, rc_green, "\n Hello Small OS!\n\n");
  init_timer(30);
  init_pmm();
  init_vmm();
  init_heap();
  init_sched();
  init_fs();
  kernel_thread(thread_A, NULL);
  enable_intr();
  kernel_thread(thread_B, NULL);
  while(1) {
    asm volatile ("hlt");
  }
}

