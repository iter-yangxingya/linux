// 演示程序，用于简档(profiler)，即评估热点函数。
//

void function1() {
    int i;
    int j;
    for (i = 0; i < 100000; i++)
        j += i;
}

void function2() {
    function1();
    int i;
    int j;
    for (i = 0; i < 200000; i++)
        j = i;
}

int main() {
    int i;
    for (i = 0; i < 100; i++)
        function1();

    for (i = 0; i < 50000; i++)
        function2();
    return 0;
}
