#include <iostream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include "../inc/func1.h"
#include "../inc/func2.h"
#include "../inc/func3.h"

void processesCalc(int iterations)
{
    double x = 2.5;         // Произвольное значение x
    int pipe1[2], pipe2[2]; // Каналы для обмена данными между процессами

    if (pipe(pipe1))
    {
        std::cerr << "Ошибка создания pipe1\n";
        return;
    }
    if (pipe(pipe2))
    {
        std::cerr << "Ошибка создания pipe2\n";
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();

    // Процесс 1: вычисление formula1
    pid_t pid1 = fork();
    if (pid1 == 0)
    {                    // Дочерний процесс 1
        close(pipe1[0]); // Закрываем чтение
        std::vector<double> results1(iterations);
        for (int i = 0; i < iterations; ++i)
        {
            results1[i] = formula1(x);
        }
        write(pipe1[1], results1.data(), iterations * sizeof(double));
        close(pipe1[1]);
        exit(0);
    }
    else if (pid1 < 0)
    {
        std::cerr << "Ошибка создания процесса 1\n";
        return;
    }

    // Процесс 2: вычисление formula2
    pid_t pid2 = fork();
    if (pid2 == 0)
    {                    // Дочерний процесс 2
        close(pipe2[0]); // Закрываем чтение
        std::vector<double> results2(iterations);
        for (int i = 0; i < iterations; ++i)
        {
            results2[i] = formula2(x);
        }
        write(pipe2[1], results2.data(), iterations * sizeof(double));
        close(pipe2[1]);
        exit(0);
    }
    else if (pid2 < 0)
    {
        std::cerr << "Ошибка создания процесса 2\n";
        return;
    }

    // Родительский процесс ожидает завершения дочерних и читает данные
    close(pipe1[1]);
    close(pipe2[1]);

    std::vector<double> results1(iterations);
    std::vector<double> results2(iterations);

    read(pipe1[0], results1.data(), iterations * sizeof(double));
    read(pipe2[0], results2.data(), iterations * sizeof(double));

    close(pipe1[0]);
    close(pipe2[0]);

    waitpid(pid1, nullptr, 0);
    waitpid(pid2, nullptr, 0);

    auto end_step1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_step1 = end_step1 - start;

    // Шаг 3: вычисление formula3 (последовательно)
    auto start_step2 = std::chrono::high_resolution_clock::now();

    std::vector<double> results3(iterations);
    for (int i = 0; i < iterations; ++i)
    {
        results3[i] = formula3(results1[i], results2[i]);
    }

    auto end_step2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration_step2 = end_step2 - start_step2;

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> total_duration = end - start;

    // Вывод результатов
    std::cout << "Параллельные вычисления через процессы:\n";
    std::cout << "Iterations: " << iterations << std::endl;
    std::cout << "Step 1 (formula1 & formula2 parallel): " << duration_step1.count() << " sec" << std::endl;
    std::cout << "Step 2 (formula3 sequential): " << duration_step2.count() << " sec" << std::endl;
    std::cout << "Total time: " << total_duration.count() << " sec" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}