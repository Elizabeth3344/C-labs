#include <iostream>
#include <chrono>
#include "../inc/func1.h"
#include "../inc/func2.h"
#include "../inc/func3.h"

void sequentialСalcOpt(int iterations)
{
    double x = 2.5; // Произвольное значение

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i)
    {
        volatile double res1 = formula1(x);
        volatile double res2 = formula2(x);
        volatile double res3 = formula3(res1, res2);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    std::cout << "Последовательные вычисления (с оптимизацией компилятора):\n";
    std::cout << "Iterations: " << iterations << ", Time: " << duration.count() << " sec\n";
    std::cout << "----------------------------------------" << std::endl;
}