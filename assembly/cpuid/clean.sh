#!/bin/sh

echo "begin cleanning cpuid build's object..."

list="cpuid cpuid.o"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

echo "clean done!"

exit 0
