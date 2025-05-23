cmake_minimum_required(VERSION 3.10)
project(parallel_lang)

# Настройки компилятора
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Добавляем исполняемый файл из одного исходника
add_executable(parallel_lang ../src/parallelLang.cpp)

# Для многопоточности (нужно для std::thread)
find_package(Threads REQUIRED)
target_link_libraries(parallel_lang PRIVATE Threads::Threads)