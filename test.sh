#!/bin/sh

qemu-system-i386 \
  -cdrom build/szczos.iso \
  -hda disk/disk.img \
  -boot d  # Boot from CD first
