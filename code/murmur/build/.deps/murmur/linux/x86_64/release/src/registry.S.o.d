{
    files = {
        "src/registry.S"
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
    depfiles = "build/.objs/murmur/linux/x86_64/release/src/registry.S.o: src/registry.S\
"
}