#!/bin/sh

qemu-system-i386 \
  -cdrom build/szczos.iso \
  -hda build/disk.img \
  -boot d  # Boot from CD first
