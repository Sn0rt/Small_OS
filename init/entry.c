#include "console.h"
#include "debug.h"
#include "gdt.h"
#include "idt.h"
#include "timer.h"
#include "vmm.h"
#include "pmm.h"

// 开启分页过后multiboot数据指针
multiboot_t *glb_mboot_ptr;

// 开启分页过后的内核栈
uint8_t kern_stack[STACK_SIZE];

/* 内核使用的临时页表和页目录
 * 地址页对齐,内存0-640k肯定是空闲的
 */
__attribute__((section(".init.data"))) pgd_t *pgd_tmp = (pgd_t *)0x1000;
__attribute__((section(".init.data"))) pgd_t *pte_low = (pgd_t *)0x2000;
__attribute__((section(".init.data"))) pgd_t *pte_high = (pgd_t *)0x3000;


// 内核初始化
void kern_init()
{
  init_debug();
  init_gdt();
  init_idt();
  init_pmm();

  console_clear();
  printk_color(rc_black, rc_green, "Hello Small OS!\n\n");
  asm volatile("int $0x01");
  asm volatile("int $0x02");
  init_timer(200);
  //    asm volatile("sti");

  printk("kernel in memory start: 0x%08X\n", kern_start);
  printk("kernel in memory end: 0x%08X\n", kern_end);
  printk("kernel in memory used: %dKB\n", (kern_end - kern_start + 1023) / 1024);


  show_memory_map();
  printk_color(rc_black, rc_green, "\nThe count of Phy Memory page is: %u\n\n", phy_page_count);

  uint32_t allc_addr = NULL;
  printk("Test physical Memory alloc:\n");
  for (int cx = 0; cx < 5; cx++){
    allc_addr = pmm_alloc_page();
    printk_color(rc_black, rc_red, "%d: Alloc physical addr 0x%08x\n", cx, allc_addr);
  }
  while(1) {
    asm volatile ("hlt");
  }
}

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
  asm volatile ("mov %0, %%cr3\n\t"
                :
                :"r"(pgd_tmp));

  /* 启用分页,将cr0的分页标志置为1 */
  uint32_t cr0;
  asm volatile ("mov %%cr0, %0\n\t"
                : "=r" (cr0));
  cr0 |= 0x80000000;
  asm volatile("mov %0, %%cr0\n\t"
               :
               :"r" (cr0));

  /* 切换内核线程 */
  uint32_t kern_stack_top = ((uint32_t)kern_stack + STACK_SIZE) & 0xFFFFFFF0;
  asm volatile ("mov %0, %%esp\n\t"
                "xor %%ebp, %%ebp\n\t"
                :
                :"r" (kern_stack_top));
  /* 更新全局multiboot指针 */
  glb_mboot_ptr = glb_mboot_ptr_tmp + PAGE_OFFSET;

  /* 内核开始初始化 */
  kern_init();
}
