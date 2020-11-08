#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/macos.kernel isodir/boot/macos.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "macos" {
	multiboot /boot/macos.kernel
}
EOF
grub-mkrescue -o macos.iso isodir