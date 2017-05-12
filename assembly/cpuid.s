# cpuid.s for get cpu vender information

.section .data
output:
    .ascii "The processor Vender ID is 'xxxxxxxxxxxx'\n"
.section .text
.global _start
_start:
    # for cpuid.
    movl $0, %eax
    cpuid

    # copy cpuid output to label output 'xxxxxxxxxxxx';
    movl $output, %edi
    movl %ebx, 28(%edi)
    movl %edx, 32(%edi)
    movl %ecx, 36(%edi)

    # call system call 'ssize_t write(int fd, const void *data, size_t dlen)';
    movl $4, %eax
    movl $1, %ebx
    movl $output, %ecx
    movl $42, %edx
    int $0x80

    # call system call 'void exit(int exit_code)';
    movl $1, %eax
    movl $0, %ebx
    int $0x80

# compile:
#   as -o cpuid.o cpuid.s
#   ld -o cpuid cpuid.o
# if you use GCC for compile, you should modify:
#   .global main
#   main:
#   ......
# after modify source use the following command:
#   gcc -o cpuid cpuid.s
# WARNING:
# 64bit system compile need use the following command:
# as --32 -o <obj file> <source file>
# ld -s -m elf_i386 -o <bin file> <obj file list>
