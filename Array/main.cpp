// Массив int[10], взять указатель (тип можно варировать) на первый элемент 
// и с помощью арифметики указателей вывести 4 элемент массива.

#include <iostream>


template<class T>
void print(T* arr) {
    if (arr == nullptr) {
        return;
    }

    const size_t elementPos = 3;

    if ((arr + elementPos) == nullptr) {
        std::cout << "Element is nullptr";
    }

    std::cout << *(arr + 3) << std::endl;
}


int main() {
    const int size = 10;

    int arr[size] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
    double arrDbl[size] = {1.2, 2.2, 3.2, 4.2, 5.2, 6.2, 7.2, 8.2, 9.2, 0.2};

    print(arr);
    print(arrDbl);

    return 0;
}
