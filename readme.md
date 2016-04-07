#Small OS

<h3>项目说明</h3>
small_os目的是实现一个简单的unix like系统，目的是学习操作系统原理。

<h3>目录结构</h3>

<pre><code>
.
├── boot
│   └── boot.s
├── drivers
│   ├── console.c
│   └── timer.c
├── floppy.img
├── gdt
│   ├── gdt.c
│   └── gdt_s.s
├── idt
│   ├── idt.c
│   └── idt_s.s
├── include
│   ├── common.h
│   ├── console.h
│   ├── debug.h
│   ├── elf.h
│   ├── gdt.h
│   ├── idt.h
│   ├── multiboot.h
│   ├── string.h
│   ├── timer.h
│   ├── types.h
│   └── vargs.h
├── init
│   └── entry.c
├── kernel
│   └── debug
│       ├── debug.c
│       ├── elf.o
│       └── printk.c
├── libs
│   ├── common.c
│   ├── elf.c
│   └── string.c
├── Makefile
├── mount
├── readme.md
└── scripts
    └── kernel.ld
</pre></code>

