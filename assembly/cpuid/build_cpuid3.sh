#!/bin/sh


as --32 -o cpuid3.o cpuid3.s
ld -m elf_i386 -dynamic-linker /usr/lib/libc.so.6 -L/usr/lib -L/lib -o cpuid3 cpuid3.o
