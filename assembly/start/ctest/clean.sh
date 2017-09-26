#!/bin/sh

echo "清除所有ctest相关的中间文件，二进制文件。"

list="ctest ctest.o ctest-dbg ctest.s"
for bin in $list; do
    if [ -f $bin ]; then
        rm -f $bin
    fi
done

echo "清理完毕"

exit 0
