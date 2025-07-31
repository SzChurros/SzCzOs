#!/bin/sh

# ---- Config ----
DISK_DIR="disk"
DISK_NAME="disk.img"


# ---- Clean ----
rm -rf "$DISK_DIR" || exit 1
echo "Removed old disk dir..."


# ---- Create Disk Image ----
echo "Creating disk image..."
mkdir $DISK_DIR
dd if=/dev/zero of="$DISK_DIR/$DISK_NAME" bs=512 count=131072
echo "Disk image created: $DISK_DIR/$DISK_NAME"