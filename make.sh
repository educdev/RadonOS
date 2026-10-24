clang --target=i386-elf -ffreestanding -fno-pic -fno-pie -fno-stack-protector -fno-builtin -c main.c -o main.o
ld.lld -m elf_i386 \
    -T /usr/local/share/murmur/linker.ld \
    main.o \
    --whole-archive /usr/local/lib/libmurmur.a \
    --no-whole-archive \
    -o o.elf
llvm-objcopy -O binary o.elf RadonOS.bin
qemu-system-i386 -enable-kvm -drive format=raw,file=RadonOS.bin -vga std
