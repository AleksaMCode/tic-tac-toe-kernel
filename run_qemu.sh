cp kernel.bin isodir/boot/KernelXO.bin
echo Making iso...
grub-mkrescue -o KernelXO.iso isodir
echo Done!
echo Running QEMU simulation...
qemu-system-x86_64 -cdrom KernelXO.iso
#echo Done!
echo Cleaning up...
rm KernelXO.iso
echo Done!