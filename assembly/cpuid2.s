# cpuid2.s for use c lib printf.

.section .data
output:
    .asciz "The processor Vender ID is '%s'\n"
.section .bss
    .lcomm buffer, 12
.section .text
.global _start
_start:
    movl $0, %eax
    cpuid

    movl $buffer, %edi
    movl %ebx, (%edi)
    movl %edx, 4(%edi)
    movl %ecx, 8(%edi)

    # push stack and call function.
    # 32bit...
    # push $buffer
    # push $output
    # 64bit...
    # rdi rsi rdx for 3 argument push.
    # pushl not supported at 64bit linux.
    movq $output, %rdi
    movq $buffer, %rsi
    call printf

    # clear the stack frame pointer
    # 64bit no need the following restore stack frame.
    #addl $8, %esp

    #push $0
    movq $0, %rdi
    call exit

# compile
#   as -o cpuid2.o cpuid2.s
#   ld -o cpuid2 cpuid2.o
