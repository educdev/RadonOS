clang --target=i386-elf -ffreestanding -fno-pic -fno-pie -fno-stack-protector -fno-builtin -c main.c -o main.o
ld.lld -m elf_i386 \
    -T /usr/local/share/murmur/linker.ld \
    main.o \
    --whole-archive /usr/local/lib/libmurmur.a \
    --no-whole-archive \
    -o o.elf
llvm-objcopy -O binary o.elf RadonOS.bin
dd if=/dev/zero of=radon_pad.bin bs=1M count=100 
dd if=RadonOS.bin of=radon_pad.bin conv=notrunc
qemu-img convert -f raw -O vmdk radon_pad.bin radon_final.vmdk
qemu-img convert -f raw -O vdi radon_pad.bin radon_final.vdi