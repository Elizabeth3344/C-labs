#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <atomic>
#include "../inc/func1.h"
#include "../inc/func2.h"
#include "../inc/func3.h"

void threadsCalc(int iterations)
{
    double x = 2.5; // Произвольное значение x
    std::vector<double> results1(iterations);
    std::vector<double> results2(iterations);
    std::vector<double> results3(iterations);

    // Шаг 1: Параллельное вычисление formula1 и formula2
    auto start = std::chrono::high_resolution_clock::now();

    std::thread thread1([&]()
                        {
        for (int i = 0; i < iterations; ++i) {
            results1[i] = formula1(x);
        } });

    std::thread thread2([&]()
                        {
        for (int i = 0; i < iterations; ++i) {
            results2[i] = formula2(x);
        } });

    thread1.join();
    thread2.join();

    auto end_step1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_step1 = end_step1 - start;

    // Шаг 2: Последовательное вычисление formula3
    auto start_step2 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < iterations; ++i)
    {
        results3[i] = formula3(results1[i], results2[i]);
    }

    auto end_step2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_step2 = end_step2 - start_step2;

    // Общее время
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_duration = end - start;

    // Вывод результатов
    std::cout << "Параллельные вычисления через потоки:\n";
    std::cout << "Iterations: " << iterations << std::endl;
    std::cout << "Step 1 (formula1 & formula2 parallel): " << duration_step1.count() << " sec" << std::endl;
    std::cout << "Step 2 (formula3 sequential): " << duration_step2.count() << " sec" << std::endl;
    std::cout << "Total time: " << total_duration.count() << " sec" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}
