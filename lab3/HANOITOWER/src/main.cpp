#include <iostream>
#include <list>
using namespace std;
#include "../inc/towerOfHanoi.h"

int main()
{
    int N = 3;

    // аллоцируем память в куче (оперативной памяти)
    list<string> *steps = new list<string>;

    // передаем в качестве аргумента в функцию
    towerOfHanoi(N, 'A', 'C', 'B', steps);
    // после выполнения функции двусвязный список steps заполнен последовательностью действий

    // тут пробежимся по нашему двусвязному списку и проверим последовательность
    for (const std::string &step : *steps)
    {
        cout << step;
    }

    // освобождаем ранее занятую память
    delete steps;

    return 0;
}