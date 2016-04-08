#ifndef INCLUDE_PMM_H
#define INCLUDE_PMM_H

#include "multiboot.h"

/* 内核文件在内存里面起始和结束位置.
 * 在链接文件里面要求链接定义
  */
extern uint8_t kern_start[];
extern uint8_t kern_end[];

// 输出BIOS提供的内存布局.
extern void show_memory_map();

#endif
