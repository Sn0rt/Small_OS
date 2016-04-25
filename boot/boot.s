;---------------------------------------
; Kernel start from here
;---------------------------------------


MBOOT_HEADER_MAGIC  equ     0x1BADB002  ; Magic number
MBOOT_PAGE_ALIGN    equ     1 << 0      ; 0号位表示所有引导模块将4k边界对齐
MBOOT_MEM_INFO      equ     1 << 1      ; 1表示通过multiboot信息结构的mem_*可用
MBOOT_HEADER_FLAGS  equ     MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ     -(MBOOT_HEADER_MAGIC + MBOOT_HEADER_FLAGS)

[BITS 32]
section .init.text

dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM

[GLOBAL start]
[GLOBAL mboot_ptr_tmp]
[EXTERN kern_entry]

start:
        cli                         ; shutdown the interrupt
        mov esp, STACK_TOP          ; setup kernel's stack
        mov ebp, 0
        and esp, 0FFFFFFF0H         ; stack address align to 16
        mov [mboot_ptr_tmp], ebx
        call kern_entry

section             .init.data
stack:  times       1024    db  0
mboot_ptr_tmp:          dd  0 ;	未开启分页临时的数据指针

STACK_TOP equ $-stack-1         ; The top of kernel stack
