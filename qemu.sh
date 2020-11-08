#!/bin/sh
set -e
#. ./iso.sh

#qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom macos.iso
. ./config.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -kernel kernel/macos.kernel