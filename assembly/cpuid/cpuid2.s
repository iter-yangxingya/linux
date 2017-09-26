# cpuid2.s for gcc compile and link. gcc use main as a entry for application.
# gcc编译链接时，用main作为入口。
# 注意：经过测试在gcc4.8.5(centos7)中，并不需要这样以main为入口。
#   用原来的_start作为入口即可，如果完全用gcc一条命令进行编译和链接，若不为_start入口，
#   可以考虑添加-e选项，指定入口函数。

.section .data
output:
    .ascii "Vender ID:xxxxxxxxxxxx!\n"
.section .text
.global main
main:
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
