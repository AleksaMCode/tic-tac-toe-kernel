#!/bin/bash
echo Building kernel...

nasm -felf32 boot.s -o boot.o
nasm -felf32 gdt.s -o gdt.o
nasm -felf32 interrupt.s -o interrupt.o
nasm -felf32 allocate.s -o allocate.o

# Compile C sources.
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o descriptor_tables.o descriptor_tables.c
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o common.o common.c
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o main.o main.c
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o monitor.o monitor.c
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o isr.o isr.c
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o timer.o timer.c
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o kb.o kb.c
gcc -m32 -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o tictactoe.o tictactoe.c

# Link all your files.
ld -m elf_i386 -T link.ld -o kernel.bin boot.o main.o common.o monitor.o descriptor_tables.o gdt.o timer.o isr.o interrupt.o kb.o tictactoe.o allocate.o

# Clean up.
echo Cleaning...
rm *.o
echo Done!
