#ifndef INCLUDE_VMM_H
#define INCLUDE_VMM_H

#include "types.h"
#include "idt.h"

// 内核偏移地址
#define PAGE_OFFSET 0xc0000000

/* P位表示存在(present)标志,用于指明对地址转换
 * 0表示无效, 1表示有效.
 * 当前P = 0; 那么除表示无效外,其余位可以供程序自己使用
 */
#define PAGE_PRESENT 0x1

/* R/W - 位1是读/写(read/write)标志.
 * 如果等于1,表示页面可以被读,写或者执行.
 * 如果为0, 表示页面只读或可执行.
 * 当处理器运行在超级用户级别(DPL 0,1, 2),则R/W不起作用.
 * 页目录项中的R/W位对其所映射的所有页面起作用.
 */
#define PAGE_WRITE 0x2

/* U/S - 位2是用户/超级用户标志
 * 如果为1, 那么运行在任何特权级上的程序都可以访问该页面
 * 如果为0, 那么页面只能被运行在超级用户特权级上的程序所访问.
 * 页目录项中的U/S位对其所映射的所有页面起作用.
 */
#define PAGE_USER 0x4

/* 虚拟分页大小 */
#define PAGE_SIZE 4096

/* 页掩码,用于4k对齐 */
#define PAGE_MASK 0xFFFFF000

/* 获取一个地址的页目录项 */
#define PGD_INDEX(x) (((x) >> 22) & 0x3FF)

/* 获取一个地址的页表项 */
#define PTE_INDEX(x) (((x) >> 12) & 0x3FF)

/* 获取一个地址的页内偏移 */
#define OFFSET_INDEX(x) ((x) & 0xFFF)

/* 页目录数据类型 */
typedef uint32_t pgd_t;

/* 页表数据类型 */
typedef uint32_t pte_t;

/* 页目录成员数量 */
#define PGD_SIZE (PAGE_SIZE/sizeof(pte_t))

/* 页表成员数 */
#define PTE_SIZE (PAGE_SIZE/sizeof(uint32_t))

/* 映射512MB内存所需要的页表数 */
#define PTE_COUNT 128

/* 内核页目录区域 */
extern pgd_t pgd_kern[PGD_SIZE];

/* 初始化虚拟内存 */
void init_vmm();

/* 更换当前的页目录 */
void switch_pgd(uint32_t pd);

/* 使用flags指出页的权限,把pa映射到va */
void map(pgd_t *pgd_now, uint32_t va, uint32_t pa, uint32_t flags);

/* 取消虚拟地址va的物理映射 */
void unmap(pgd_t *pgd_now, uint32_t va);

/* 若va映射到物理地址则返回1
 * 同时如果pa不是空指针则把物理地址写入pa参数
 */
uint32_t get_mapping(pgd_t *pgd_now, uint32_t va, uint32_t *pa);

/* 页错误中断的函数处理 */
void page_fault(pt_regs *regs);

#endif
