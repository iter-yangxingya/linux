// cpuid3.s for call c-standard-library version.


.section .data
output:
    .asciz "Vender ID:%s"
.section .bss
    .lcomm buffer, 12
.section .text
.global _start
_start:
    movl $0, %eax
    cpuid

    movl $buffer, %edi
    movl %ebx, 0(%edi)
    movl %edx, 4(%edi)
    movl %ecx, 8(%edi)

    pushl $buffer
    pushl $output
    call printf

    addl $8, %esp

    pushl $0
    call exit

