#include <iostream>
#include <cstdlib> // для atof()
#include "../inc/power_func.h"

int main(int argc, char *argv[])
{
    // Проверка количества аргументов (должно быть 4: имя программы + 3 аргумента)
    if (argc != 4)
    {
        std::cerr << "Использование: " << argv[0] << " <операнд1> <оператор> <операнд2>\n";
        std::cerr << "Допустимые операторы: +, -, ^\n";
        return 1;
    }

    // Парсинг аргументов
    double operand1 = atof(argv[1]); // atof преобразует строку в число
    char op = argv[2][0];            // берём первый символ оператора
    double operand2 = atof(argv[3]);

    double result;

    // Выполнение операции
    switch (op)
    {
    case '+':
        result = operand1 + operand2;
        break;
    case '-':
        result = operand1 - operand2;
        break;
    case '^':
        result = power(operand1, static_cast<int>(operand2)); // static_cast преобразует один тип данных в другой (в какой, указанно в <>)
        break;
    default:
        std::cerr << "Ошибка: неизвестный оператор '" << op << "'\n";
        std::cerr << "Допустимые операторы: +, -, ^\n";
        return 1;
    }

    // Вывод результата
    std::cout << "Результат: " << result << std::endl;

    return 0;
}