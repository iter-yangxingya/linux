#!/bin/sh

source=section.c
binary=section
assembly=section.s

list="$binary $assembly"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

echo "begin compiling..."
gcc -m32 -o $assembly -S $source
gcc -o $binary $source
echo "compiled!"

exit 0
