//
// \file new_feature.cpp
// \brief new_feature.cpp for cxx11 new feature test.
//
// \ compile need: g++ -std=c++11 -pthread new_feature.cpp
//      because thread need pthread for usage, if no this
//      option, then will run-error...

#include <thread>
#include <atomic>
#include <iostream>

int main(int argc, char **argv) {

    std::atomic<int> value{0};
    std::thread thr1([&]() {
        int times = 1000000;
        while (times--) {
            value++;
            std::cout << "value=" << value.load() << std::endl;
        }
    });

    std::thread thr2([&]() {
        int times = 1000000;
        while (times--) {
            value++;
            std::cout << "value=" << value.load() << std::endl;
        }
    });

    thr1.join();
    thr2.join();

    return 0;
}
