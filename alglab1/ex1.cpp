#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    cout << "Введите количество карточек: ";
    cin >> n;

    // Массив-счетчик, в котором индекс - число от 0 до 20, а элемент - количество вхождений числа
    const int range = 21;        // размер
    vector<int> count(range, 0); // Инициализируем нулями

    cout << "Введите номера карточек (от 0 до 20):" << endl;
    for (int i = 0; i < n; ++i)
    {
        int num;
        cin >> num;
        if (num >= 0 && num < range)
        {
            count[num]++;
        }
        else
        {
            cout << "Ошибка: число " << num << " выходит за допустимый диапазон." << endl;
            return 1;
        }
    }

    cout << "Отсортированные номера карточек:" << endl;

    // Выводим отсортированный массив
    for (int num = 0; num < range; ++num)
    {
        // Выводим число num столько раз, сколько оно встретилось
        for (int j = 0; j < count[num]; ++j)
        {
            cout << num << " ";
        }
    }
    cout << endl;

    return 0;
}