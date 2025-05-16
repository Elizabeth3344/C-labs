cmake_minimum_required(VERSION 3.10)
project(ParallelComputingComparison)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Исходные файлы
set(SOURCES
    ../src/sequentialСalc.cpp    # Последовательные вычисления (базовая версия)
    ../src/sequentialСalcOpt.cpp # Оптимизированные последовательные вычисления
    ../src/threadsCalc.cpp       # Параллельные вычисления с потоками
    ../src/processesCalc.cpp     # Параллельные вычисления с процессами
    ../src/main.cpp
    ../src/func1.cpp
    ../src/func2.cpp
    ../src/func3.cpp              
)

# Создаем исполняемый файл
add_executable(compute ${SOURCES})

# Для процессов требуется unistd.h (Unix)
if(UNIX)
    target_compile_definitions(compute PRIVATE _GNU_SOURCE)
endif()