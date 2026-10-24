{
    files = {
        "src/registry.S"
    },
    depfiles = "build/.objs/murmur/linux/i386/release/src/registry.S.o: src/registry.S\
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