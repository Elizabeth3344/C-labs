#include <iostream>      //стандартная библиотека ввода-вывода в C++, которая позволяет программам взаимодействовать с пользователем через консоль (чтение с клавиатуры и вывод на экран)
#include <chrono>        // Для замера времени
#include <limits>        // Для std::numeric_limits
#include "../inc/func.h" // Подключаем нашу функцию

int main()
{
    bool repeat = true;

    while (repeat)
    {
        int iterations;
        std::cout << "Введите количество итераций (или нечисло для выхода): ";

        // Проверка ввода
        if (!(std::cin >> iterations))
        {
            std::cout << "Введено не число. Программа завершается." << std::endl;
            break;
        }

        if (iterations <= 0)
        {
            std::cout << "Число итераций должно быть положительным." << std::endl;
            continue;
        }

        float x = 2.0; // Можно изменить или запросить у пользователя

        // Замер времени
        auto start = std::chrono::high_resolution_clock::now();

        // Цикл вычислений
        for (int i = 0; i < iterations; ++i)
        {
            my_func(x); // Вызов функции из func.cpp
        }

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;

        // Вывод результатов
        std::cout << "Вычисление выполнено " << iterations << " раз." << std::endl;
        std::cout << "Общее время выполнения: " << duration.count() << " секунд." << std::endl;
        std::cout << "Среднее время на итерацию: " << duration.count() / iterations << " секунд." << std::endl;

        // Очистка буфера ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Запрос на повтор
        char answer;
        std::cout << "Хотите выполнить еще один запуск? (y/n): ";
        std::cin >> answer;

        if (answer != 'y' && answer != 'Y')
        {
            repeat = false;
        }

        // Очистка буфера ввода
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return 0;
}