#!/bin/sh

# cpuid2.s build
# 64位系统需要处理：
#   1. 编译时需要使用32位的选项。
#       b. gcc -m32 -o cpuid cpuid.s
#   需要去除标准库的支持（-nostdlib选项）。

list="cpuid2"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

opt=""
art="release"
if [ $# -ge 1 ]; then
    art=$1
fi

if [ $art = "debug" ]; then
    opt="-gstabs"
elif [ $arg = "release" ]; then
    opt=""
elif [ $arg = "-h" ]; then
    echo "usage: "
    echo "  ./build_cpuid2.sh [debug/release]"
    echo "  if you no [debug/release] argument, default is release."
    exit 0
elif [ $arg = "--help" ]; then
    echo "usage: "
    echo "  ./build_cpuid2.sh [debug/release]"
    echo "  if you no [debug/release] argument, default is release."
    exit 0
else
    echo "error debug/release version!"
    exit 1
fi

#gcc -o cpuid2 cpuid2.s
gcc -m32 -nostdlib $opt -e main -o cpuid2 cpuid2.s
echo "build successful!"

exit 0
