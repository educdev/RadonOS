-- SPDX-License-Identifier: Apache-2.0

set_project("murmur")
set_version("26.10")

set_toolchains("clang")
add_rules("mode.debug", "mode.release")

target("murmur")
    set_kind("static")
    set_arch("i386")

    add_files("src/*.S")
    add_asflags("--target=i386-none-elf", {force = true})

    add_includedirs("include", {public = true})

    add_headerfiles("include/(murmur/*.h)")
    add_installfiles("linker.ld", {prefixdir = "share/murmur"})