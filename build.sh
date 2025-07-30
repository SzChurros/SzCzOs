#!/bin/sh

rm -rf build

echo "Removed old build dir..."

mkdir build
mkdir build/graphics
mkdir build/drivers

echo "Redid folder structure..."

echo Compiling...
nasm -f elf32 src/boot.s -o build/boot.o
gcc -m32 -ffreestanding -nostdlib -c src/kernel.c -o build/kernel.o
gcc -m32 -ffreestanding -nostdlib -c src/szczos.c -o build/szczos.o
gcc -m32 -ffreestanding -nostdlib -c src/asmc.c -o build/asmc.o
gcc -m32 -ffreestanding -nostdlib -c src/shell.c -o build/shell.o
gcc -m32 -ffreestanding -nostdlib -c src/graphics/vga_colors.c -o build/graphics/vga_colors.o
gcc -m32 -ffreestanding -nostdlib -c src/drivers/ps2.c -o build/drivers/ps2.o

echo Linking...
ld -m elf_i386 -T linker.ld -o build/kernel.bin build/boot.o build/kernel.o build/szczos.o build/graphics/vga_colors.o build/asmc.o build/drivers/ps2.o build/shell.o


echo 'Making the iso...'
mkdir -p build/boot/grub
cp build/kernel.bin build/boot/
cp grub.cfg build/boot/grub/
grub-mkrescue -o build/szczos.iso build



echo Done!