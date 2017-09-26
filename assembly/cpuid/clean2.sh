#!/bin/sh

echo "begin cleanning cpuid2 build's object..."

list="cpuid2"
for out in $list; do
    if [ -f $out ]; then
        rm -f $out
    fi
done

echo "clean done!"

exit 0
