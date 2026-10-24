{
    files = {
        "src/bios_entry.S"
    },
    depfiles = "build/.objs/murmur/linux/i386/release/src/bios_entry.S.o:   src/bios_entry.S src/registry.inc\
",
    depfiles_format = "gcc",
    values = {
        "/usr/bin/clang",
        {
            "-Qunused-arguments",
            "--target=i686-linux-gnu",
            "-fvisibility=hidden",
            "-O3",
            "-Iinclude",
            "--target=i386-none-elf"
        }
    }
}