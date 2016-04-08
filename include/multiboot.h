#ifndef _INCLUDE_MULTIBOOT_H
#define _INCLUDE_MULTIBOOT_H

#include "types.h"

/* 启动后,在32位内核进入点,机器状态如下
 * 1. cs指向基地址0x00000000,限长1-4G的代码段描述符
 * 2. ds, ss, es, fs, gs 指向基地址0x00000000,限长1-4G的数据段描述符
 * 3. A20地址线已经被打开
 * 4. 页机制被禁止
 * 5. 中断被禁止
 * 6. EAX = 0x2BADB002
 * 7. 系统信息和启动信息块的线性地址保存在ebx中.
 */

typedef struct multiboot_t {
  /* multiboot version info */
  uint32_t flags;

  /* mem_lower和mem_upper分别指出低端和高端内存的大小,单位是k
   * 低端内存的首地址是0,高端内存首地址是1M
   * 低端内存的最大值可能是640k
   * 高端内存的最大值可能是最大值-1M
   */
  uint32_t mem_lower;
  uint32_t mem_upper;

  /* which device can be bootable  */
  uint32_t boot_device;

  /* kernel command line */
  uint32_t cmdline;

  /* The boot modules list */
  uint32_t mods_count;
  uint32_t mods_addr;

  /* ELF format section head
   */
  uint32_t num;
  uint32_t size;
  uint32_t addr;
  uint32_t shndx;

  /* Provide from BIOS buffer
   * mmap_addr is start address
   * mmap_length is length of address
   */
  uint32_t mmap_length;
  uint32_t mmap_addr;

  /* first drives physical address */
  uint32_t drives_length;
  uint32_t drives_addr;

  /* ROM configure table */
  uint32_t config_table;

  /* bootloader name */
  uint32_t boot_loader_name;
  uint32_t apm_table;

  uint32_t vbe_control_info;
  uint32_t vbe_mode_info;
  uint32_t vbe_mode;
  uint32_t vbe_interface_seg;
  uint32_t vbe_interface_off;
  uint32_t vbe_interface_len;
} __attribute__((packed)) multiboot_t;

/* size: the size of struct
 * base_addr_low: is start address
 * 32base_addr_high: top 32 bit of start address
 * length_low: the lower of memory region
 * 32length_high: the toper 32 bit of memory region
 * type: 是内存可用信息1代表可用,其他的代表保留区域
 */
typedef struct mmap_entry_t {
  uint32_t size;
  uint32_t base_addr_low;
  uint32_t base_addr_high;
  uint32_t length_low;
  uint32_t length_high;
  uint32_t type;
} __attribute__((packed)) mmap_entry_t;

extern multiboot_t *glb_mboot_ptr;

#endif
