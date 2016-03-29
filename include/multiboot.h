#ifndef _INCLUDE_MULTIBOOT_H
#define _INCLUDE_MULTIBOOT_H

#include "types.h"

typedef struct multiboot_t {
    /* version info */
    uint32_t flags;

    /* mem_lower start from 0x00000000 and max value 640k
     * mem_upper start from 0x00000400 and max value
     * is maybe max value-1M
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
     * dx == index
     */
    uint32_t num;
    uint32_t size;
    uint32_t addr;
    uint32_t shndx;

    /* Provide from BIOS buffer
     * mmap_addr is start address
     * mmap_length is length of address
     */
    uint32_t mmap_addr;
    uint32_t mmap_length;

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
 */
typedef struct mmap_entry_t {
    uint32_t size;
    uint32_t base_addr_low;
    uint32_t base_addr_high;
    uint32_t length_low;
    uint32_t length_high;
} __attribute__((packed)) mmap_entry_t;

extern multiboot_t *glb_mboot_ptr;

#endif
