#!/bin/sh

echo 开始清理简档器生成的中间文件。

list="demo gmon.out demo_prof.txt"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

echo 清理完毕。
exit 0
