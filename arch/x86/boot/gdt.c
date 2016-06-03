#include "gdt.h"
#include "string.h"

// 全局描述类型长度
#define GDT_LENGTH 5

// 全局描述表定义
gdt_entry_t gdt_entries[GDT_LENGTH];

// GDTR
gdt_ptr_t gdt_ptr;

static void gdt_set_gate(int32_t num, uint32_t base,
                         uint32_t limit, uint8_t access, uint8_t gran);

// 声明内核线程地址
extern uint32_t stack;

void init_gdt()
{
    //全局描述表界限 e.g. 从0开始, 所以总要-1
    gdt_ptr.limit = sizeof(gdt_entry_t) * GDT_LENGTH - 1;
    gdt_ptr.base = (uint32_t) & gdt_entries;

    // intel flat mode
    gdt_set_gate(0, 0, 0, 0, 0); // Intel 文档要求
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9a, 0xCF); // 指令段
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // 数据段
    gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFa, 0xCF); // 用户模式代码段
    gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // 用户模式数据段

    // 加载全局描述表地址到GPTR寄存器
    gdt_flush((uint32_t) & gdt_ptr);
}

static void gdt_set_gate(int32_t num, uint32_t base,
                         uint32_t limit, uint8_t access, uint8_t gran)
{
    gdt_entries[num].base_low = (base & 0xFFFF);
    gdt_entries[num].base_middle = (base >> 16) & 0xFF;
    gdt_entries[num].base_high = (base >> 24) & 0xFF;

    gdt_entries[num].limit_low = (limit & 0xFFFF);
    gdt_entries[num].granularity = (limit >> 16) & 0x0F;

    gdt_entries[num].granularity |= gran & 0xF0;
    gdt_entries[num].access = access;
}
