#!/bin/sh

list="demo gmon.out demo_prof.txt"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

echo "gprof用法：检测出程序中的热点，耗时最多的地方。"
echo "  usage:"
echo "    gcc -o <binary> <source> -pg"
echo "    ./<binary>"
echo "    gprof <binary>"
echo "  note:"
echo "    1. 编译时需要添加pg选项。"
echo "    2. 运行二进制文件后会在当前目录生产gmon.out文件。"
echo "    3. 通过调用gprof命令，联合输出的gmon.out文件，产生性能报告输出，可以重定向到输出文件。"
echo "下面是输出结果："

gcc -o demo demo.c -pg
./demo
gprof demo > demo_prof.txt
cat demo_prof.txt

if [ -f demo_prof.txt ]; then
    echo "all thing is done, please check demo_prof.txt file."
    exit 0
else
    echo "there be a error happen, please check!"
    exit 1
fi
