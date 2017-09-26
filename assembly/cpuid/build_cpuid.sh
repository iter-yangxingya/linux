#!/bin/sh

# cpuid.s build
# 64位系统需要处理：
#   1. 编译时需要使用32位的选项。
#       a. as --32 -o cpuid.o cpuid.s
#       b. gcc -m32 -o cpuid.o cpuid.s
#   2. 链接时需要使用32位的选项。
#       ld -m elf_i386 -o cpuid cpuid.o

list="cpuid cpuid.o"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

arg="as"
if [ $# -ge 1 ]; then
    arg=$1
fi

dbg="release"
if [ $# -ge 2 ]; then
    dbg=$2
fi
if [ $dbg = "debug" ]; then
    dbg="-gstabs"
elif [ $dbg = "release" ]; then
    dbg=""
else
    echo "error debug/release target argument."
    exit 1
fi

echo "arg=$arg, dbg=$dbg"

if [ $arg = "as" ]; then
    as --32  $dbg -o cpuid.o cpuid.s
    ld -m elf_i386 -o cpuid cpuid.o
    echo "build successful!"
elif [ $arg = "gcc" ]; then
    gcc -m32 $dbg -c -o cpuid.o cpuid.s
    ld -m elf_i386 -o cpuid cpuid.o
    echo "build successful!"
elif [ $arg = "-h" ]; then
    echo "usage:"
    echo "  ./build_cpuid [as/gcc [debug/release]]"
    echo "  as as default if no argument."
    echo "  debug as default for debug argument."
elif [ $arg = "--help" ]; then
    echo "usage:"
    echo "  ./build_cpuid [as/gcc [debug/release]]"
    echo "  as as default if no argument."
    echo "  debug as default for debug argument."
else
    echo "error argument!"
    exit 1
fi

exit 0
