//
// 测试c程序中的不同段。
// 数据段，bss段，文本段。
//  1. 文本段是指令码的地方，是必须的。
//  2. 数据段是声明带有初始值的数据元素。
//  3. bss段是声明使用0初始化的数据元素。
// note: 那么bss段和数据段的区别呢？
//  不管那么多，上程序。
//
//

#include <stdio.h> // printf()

int value = 0;
int value2;

int sum(int a, int b) {
    static int ia;
    static int ib = 0;
    return a + b;
}

int main() {
    printf("hello, i am a section test... (data/bss/text/...)\n");
    return 0;
}
