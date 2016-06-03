# Makefile for Small OS

ARCH = x86
C_SOURCES = $(shell find . -name "*.c")
C_OBJECTS = $(patsubst %.c, %.o, $(C_SOURCES))
S_SOURCES = $(shell find . -name "*.s")
S_OBJECTS = $(patsubst %.s, %.o, $(S_SOURCES))

C_FLAGS = -c -Wall -m32 -ggdb -gstabs+ -nostdinc -fno-builtin -fno-stack-protector -I include
LD_FLAGS = -T arch/$(ARCH)/setup.ld -m elf_i386 -nostdlib
ASM = nasm
ASM_FLAGS = -f elf -g -F stabs

.PHONY:help update_image all run clean

all: $(S_OBJECTS) $(C_OBJECTS) link update_image

help:
	@echo "Makefile for Building Small Operating System."
	@echo -en "\n"
	@echo "Usage: make [ all | run | debug | clean ]"
	@echo  ""

.c.o:
	@echo 编译代码文件 $< ...
	$(CC) $(C_FLAGS) $< -o $@

.s.o:
	@echo 编译汇编文件 $< ...
	$(ASM) $(ASM_FLAGS) $<

link:
	@echo 链接内核文件...
	$(LD) $(LD_FLAGS) $(S_OBJECTS) $(C_OBJECTS) -o small_os

update_image:
	sudo mount floppy.img ./mount/
	sudo cp small_os ./mount/
	sleep 1
	sudo umount ./mount/

clean:
	$(RM) $(S_OBJECTS) $(C_OBJECTS) small_os

run:
	qemu-system-x86_64 -fda ./floppy.img -boot a

debug:
	qemu-system-x86_64 -S -s -fda ./floppy.img -boot a
