cmake_minimum_required(VERSION 3.10)
project(HanoiTower CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создаем исполняемый файл
add_executable(hanoi_tower
    ../src/towerOfHanoi.cpp
    ../src/main.cpp
)