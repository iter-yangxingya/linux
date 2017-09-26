# cpuid.s is for probe cpuid instruction code.
# cpuid指令通过eax寄存器获取输入，通过ebx/ecx/edx作为输出。
# 输入可以为：
#   0           厂商id字符串和支持的最大cpuid选项值。
#   1           处理器类型、系列、型号和分步信息。
#   2           处理器缓存配置。
#   3           处理器序列号。
#   4           缓存配置（线程数量、核心数量和物理属性）。
#   5           监视信息。
#   80000000h   扩展的厂商id字符串和支持的级别。
#   80000001h   扩张的处理器类型、系列、型号和分步信息。
#   80000002h~80000004h     扩展的处理器名称字符串。
# 本例子暂时输入为0.
#   输出为ebx，edx，ecx排列，为厂商id。
#
# 编译选项，当前系统如果为64位，编译为32位需要添加32位的编译选项：
#   as --32 -o cpuid.o cpuid.s
#   gcc -m32 -o cpuid.o cpuid.s
# 链接的时候需要使用 -m elf_i386选项，
# 如果汇编中调用了c运行库，则需要添加对32位运行库的支持。
#   具体的做法是：




.section .data
output:
    .ascii "Vender ID:xxxxxxxxxxxx!\n"
.section .text
.global _start
_start:
    movl $0, %eax
    cpuid

    movl $output, %edi
    movl %ebx, 10(%edi)
    movl %edx, 14(%edi)
    movl %ecx, 18(%edi)

    movl $4, %eax
    movl $1, %ebx
    movl $output, %ecx
    movl $24, %edx
    int $0x80

    movl $1, %eax
    movl $0, %ebx
    int $0x80

