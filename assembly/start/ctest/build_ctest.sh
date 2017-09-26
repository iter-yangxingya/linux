#!/bin/sh

#清理上次编译的残留文件。
list="ctest ctest.o ctest-dbg ctest.s"
for bin in $list; do
    if [ -f $bin ]; then
        rm -f $bin
    fi
done

echo 编译为二进制文件
gcc -o ctest ctest.c

echo 编译为汇编语言文件
gcc -o ctest.s -S ctest.c

echo 编译为带有调试信息的二进制文件
gcc -o ctest-dbg -gstabs ctest.c

echo 编译为中间文件
gcc -o ctest.o -c ctest.c

echo "objdump用法：将中间文件转换为指令码."
echo "  usage:"
echo "    objdump -d <objfile>"
echo "下面是输出结果："
objdump -d ctest.o

echo "all thing done!"

exit 0
