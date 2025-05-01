import time

def my_func(x):
    return x**2 - x**2 + x*4 - x*5 + x + x

def main():
    while True:
        try:
            iterations = input("Введите количество итераций (или 'q' для выхода): ")
            
            if iterations.lower() == 'q':
                print("Программа завершена.")
                break
                
            iterations = int(iterations)
            if iterations <= 0:
                print("Число итераций должно быть положительным.")
                continue
                
            x = 2.0  # Можно изменить или запросить у пользователя
            
            # Замер времени выполнения
            start_time = time.perf_counter()
            
            for _ in range(iterations):
                my_func(x)
            
            end_time = time.perf_counter()
            total_time = end_time - start_time
            
            # Вывод результатов
            print(f"\nВычисление выполнено {iterations} раз")
            print(f"Общее время выполнения: {total_time:.6f} секунд")
            print(f"Среднее время на итерацию: {total_time/iterations:.6f} секунд\n")
            
        except ValueError:
            print("Ошибка: введено не число. Программа завершена.")
            break

# Для выполнения скрипта только при прямом запуске этого файла (если этот файл будет импортироваться как модуль в другой программе, скрипт не выполнится автоматически)
if __name__ == "__main__":
    main()