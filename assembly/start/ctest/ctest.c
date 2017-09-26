//
// 测试程序，用于gcc编译为二进制文件或者汇编文件。
// gcc usage:
//  1. 编译为二进制文件。
//      gcc -o ctest ctest.c
//  2. 编译为汇编文件。
//      gcc -o ctest.s -S ctest.c
//

#include <stdio.h>  // printf()
#include <stdlib.h> // exit()

int main() {
    printf("hello, c programm will be complied to assemmbly file!\n");
    exit(0);
}
