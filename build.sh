#!/bin/sh

# ---- Config ----
KERNEL_NAME="szczos"
ISO_NAME="szczos.iso"
BUILD_DIR="build"
GRUB_CFG="grub.cfg"

# ---- Clean ----
rm -rf "$BUILD_DIR" || exit 1
echo "Removed old build dir..."

# ---- Setup ----
mkdir -p "$BUILD_DIR"/{graphics,drivers,boot/grub} || exit 1
echo "Created folder structure..."

# ---- Compile ----
echo "Compiling..."
nasm -f elf32 src/boot.s -o "$BUILD_DIR"/boot.o || exit 1
gcc -m32 -ffreestanding -nostdlib -Wall -Wextra -c \
    src/kernel.c -o "$BUILD_DIR"/kernel.o || exit 1
gcc -m32 -ffreestanding -nostdlib -Wall -Wextra -c \
    src/szczos.c -o "$BUILD_DIR"/szczos.o || exit 1
gcc -m32 -ffreestanding -nostdlib -Wall -Wextra -c \
    src/asmc.c -o "$BUILD_DIR"/asmc.o || exit 1
gcc -m32 -ffreestanding -nostdlib -Wall -Wextra -c \
    src/graphics/vga_colors.c -o "$BUILD_DIR"/graphics/vga_colors.o || exit 1
gcc -m32 -ffreestanding -nostdlib -Wall -Wextra -c \
    src/drivers/ps2.c -o "$BUILD_DIR"/drivers/ps2.o || exit 1

# ---- Link ----
echo "Linking..."
ld -m elf_i386 -T linker.ld -o "$BUILD_DIR"/kernel.bin \
    "$BUILD_DIR"/boot.o \
    "$BUILD_DIR"/kernel.o \
    "$BUILD_DIR"/szczos.o \
    "$BUILD_DIR"/graphics/vga_colors.o \
    "$BUILD_DIR"/asmc.o \
    "$BUILD_DIR"/drivers/ps2.o || exit 1

# ---- ISO ----
echo "Making the ISO..."
cp "$BUILD_DIR"/kernel.bin "$BUILD_DIR"/boot/ || exit 1
cp "$GRUB_CFG" "$BUILD_DIR"/boot/grub/ || exit 1
grub-mkrescue -o "$BUILD_DIR"/"$ISO_NAME" "$BUILD_DIR" || exit 1

echo "Done! ISO: $BUILD_DIR/$ISO_NAME"