echo Building kernel...
#nasm -f aout -o start.o new_start.asm
nasm -felf32 boot.s -o boot.o
nasm -felf32 gdt.s -o gdt.o
nasm -felf32 interrupt.s -o interrupt.o
nasm -felf32 allocate.s -o allocate.o
#/home/opt/cross/bin/i686-elf-as boot.s -o boot.o
#rem Remember this spot here: We will add 'gcc' commands here to compile C sources
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o main.o main.c
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o descriptor_tables.o descriptor_tables.c
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o common.o common.c
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o monitor.o monitor.c
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o isr.o isr.c
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o timer.o timer.c
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o kb.o kb.c
/home/opt/cross/bin/i686-elf-gcc -nostdlib -Wall -O -fstrength-reduce -fomit-frame-pointer -finline-functions -nostdinc -fno-stack-protector -fno-builtin -I./include -c -o tictactoe.o tictactoe.c

#rem This links all your files. Remember that as you add *.o files, you need to
#rem add them after start.o. If you don't add them at all, they won't be in your kernel!
ld -m elf_i386 -T link.ld -o kernel.bin boot.o main.o common.o monitor.o descriptor_tables.o gdt.o timer.o isr.o interrupt.o kb.o tictactoe.o allocate.o
echo Cleaning...
rm *.o
echo Done!