/*
 *      kernel.ld -- 针对 32-bit 链接脚本
 */
OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(start)
SECTIONS
{
        PROVIDE(kern_start = 0xc0100000);
        . = 0x100000;
        .init.text :
        {
                *(.init.text)
                . = ALIGN(4096);
        }

        .init.data :
        {
                *(.init.data)
                . = ALIGN(4096);
        }

        . += 0xc0000000;
        .text : AT(ADDR(.text) - 0xc0000000)
        {
                *(.text)
                . = ALIGN(4096);
        }
        .data : AT(ADDR(.data) - 0xc0000000)
        {
                *(.data)
                *(.rodata)
                . = ALIGN(4096);
        }
        .bss : AT(ADDR(.bss) - 0xc0000000)
        {
                *(.bss)
                . = ALIGN(4096);
        }
        .stab : AT(ADDR(.stab) - 0xc0000000)
        {
                *(.stab)
                . = ALIGN(4096);
        }

        .stabstr : AT(ADDR(.stabstr) - 0xc0000000)
        {
                *(.stabstr)
                . = ALIGN(4096);
        }

        PROVIDE(kern_end = .);
        /DISCARD/ : { *(.comment) *(.eh_frame) }
}
