;---------------------------------------
; Kernel start from here
;---------------------------------------


MBOOT_HEADER_MAGIC  equ     0x1BADB002  ; Magic number from mboot standar
MBOOT_PAGE_ALIGN    equ     1 << 0      ; Bit 0
MBOOT_MEM_INFO      equ     1 << 1
MBOOT_HEADER_FLAGS  equ     MBOOT_PAGE_ALIGN | MBOOT_MEM_INFO
MBOOT_CHECKSUM      equ     -(MBOOT_HEADER_MAGIC+MBOOT_HEADER_FLAGS)

[BITS 32]
section .text

dd MBOOT_HEADER_MAGIC
dd MBOOT_HEADER_FLAGS
dd MBOOT_CHECKSUM

[GLOBAL start]
[GLOBAL glb_mboot_ptr]
[EXTERN kern_entry]

start:
        cli                         ; shutdown the interrupt
        mov esp, STACK_TOP          ; setup kernel's stack
        mov ebp, 0
        and esp, 0FFFFFFF0H         ; stack address align to 16
        mov [glb_mboot_ptr], ebx
        call kern_entry

stop:
        hlt                         ; halt the cpu until next extern interrupt
        jmp stop                    ; shutdown the machine

section .bss                    ; undefine bss stack

stack:
        resb 32768                  ; kernel stack

glb_mboot_ptr:
        resb 4                  ; global multiboot struct

STACK_TOP equ $-stack-1         ; The top of kernel stack
