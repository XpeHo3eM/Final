// Разработайте программу, демонстрирующую создание двух потоков в C++, 
// где один поток пишет данные в переменную, а другой читает из нее, 
// с использованием мьютексов для синхронизации доступа.

#include <iostream>
#include <thread>
#include <mutex>


static int val;
static std::mutex mtx;
static std::mutex mtxOut;

void print() {
    std::lock_guard<std::mutex> lockOut(mtxOut);
    std::cout << val << std::endl;
}

void Foo(bool increment) {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);
        increment ? ++val : --val;
        lock.unlock();

        print();

        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}


int main() {
    std::thread th1(Foo, true);
    std::thread th2(Foo, false);

    th1.join();
    th2.join();

    return 0;
}