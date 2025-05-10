cmake_minimum_required(VERSION 3.10)
project(Calculator CXX)

# Настройка стандарта C++ (рекомендуется 11 или выше)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаём исполняемый файл 'calc' из исходников
add_executable(calc
    ../src/calc.cpp
    ../src/power_func.cpp
)
