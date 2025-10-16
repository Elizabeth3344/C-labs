#include <iostream>
#include <string>
#include <vector>

struct Employee
{
    std::string name;
    double salary;
};

bool shouldComeBefore(const Employee &a, const Employee &b)
{
    // сравниваем зарплату (по убыванию)
    if (a.salary > b.salary)
        return true;
    if (a.salary < b.salary)
        return false;
    // если зарплаты равны, сравниваем имена (по возрастанию)
    return a.name < b.name;
}

void quickSort(std::vector<Employee> &arr, int start, int end)
{
    // Базовый случай: массив из 1 элемента
    if (start >= end)
        return;

    // Выбираем опорный элемент из СЕРЕДИНЫ
    int mid = start + (end - start) / 2;
    Employee pivot = arr[mid];

    int left = start;
    int right = end;

    // Разделение массива относительно pivot
    while (left <= right)
    {
        // Ищем элемент слева, который должен быть СПРАВА от pivot
        while (shouldComeBefore(arr[left], pivot))
        {
            left++;
        }

        // Ищем элемент справа, который должен быть СЛЕВА от pivot
        while (shouldComeBefore(pivot, arr[right]))
        {
            right--;
        }

        // Если нашли пару для обмена
        if (left <= right)
        {
            std::swap(arr[left], arr[right]);
            left++;
            right--;
        }
    }

    // Рекурсивно сортируем левую и правую части
    quickSort(arr, start, right);
    quickSort(arr, left, end);
}

// Вспомогательная функция для удобства
void quickSort(std::vector<Employee> &arr)
{
    if (!arr.empty())
    {
        quickSort(arr, 0, arr.size() - 1);
    }
}

// Простая функция вывода
void printEmployees(const std::vector<Employee> &employees)
{
    for (const auto &emp : employees)
    {
        std::cout << emp.name << " - " << emp.salary << " руб." << std::endl;
    }
    std::cout << std::endl;
}

int main()
{

    std::vector<Employee> employees = {
        {"Иван", 50000},
        {"Мария", 75000},
        {"Алексей", 50000},
        {"Ольга", 90000}};

    std::cout << "До сортировки:" << std::endl;
    printEmployees(employees);

    quickSort(employees);

    std::cout << "После сортировки:" << std::endl;
    printEmployees(employees);

    return 0;
}
