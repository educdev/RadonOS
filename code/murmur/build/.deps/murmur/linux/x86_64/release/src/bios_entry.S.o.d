{
    files = {
        "src/bios_entry.S"
    },
    depfiles_format = "gcc",
    values = {
        "/usr/bin/clang",
        {
            "-Qunused-arguments",
            "-m64",
            "-fvisibility=hidden",
            "-O3",
            "-Iinclude",
            "--target=i386-none-elf"
        }
    },
    depfiles = "build/.objs/murmur/linux/x86_64/release/src/bios_entry.S.o:   src/bios_entry.S src/registry.inc\
"
}