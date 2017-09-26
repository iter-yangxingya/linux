#!/bin/sh

source=section.c
binary=section
assembly=section.s

echo "begin cleaning section build file..."

list="$binary $assembly"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

echo "clean done!"

exit 0
