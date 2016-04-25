#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H

#include "multiboot.h"

/* 线程栈的大小 */
#define STACK_SIZE 8192

/* 支持的最大物理内存 */
#define PMM_MAX_SIZE 0x20000000

/* 物理页框大小 */
#define PMM_PAGE_SIZE 0x1000

/* 最多支持的物理页面个数 */
#define PAGE_MAX_SIZE (PMM_MAX_SIZE / PMM_PAGE_SIZE)

/* 页码按照4096对齐 */
#define PHY_PAGE_MASK 0xfffff000

// 内核栈的栈顶
extern uint32_t kern_stack_top;

/* 动态内存分配的总页数 */
extern uint32_t phy_page_count;

/* 内核文件在内存里面起始和结束位置.
 * 在链接文件里面要求链接定义
  */
extern uint8_t kern_start[];
extern uint8_t kern_end[];

// 输出BIOS提供的内存布局.
extern void show_memory_map();

/* 初始化物理内存管理 */
void init_pmm();

/* 返回一个内存页的物理地址 */
uint32_t pmm_alloc_page();

/* 释放一个物理内存页面 */
void pmm_free_page(uint32_t);

#endif
