#ifndef TOWER_OF_HANOI_H // проверяем, не был оли определен этот файл ранее
#define TOWER_OF_HANOI_H // определяем файл, если выполнилось условие; если нет - пропускает код

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod, list<string> *steps);

#endif // завершение условия ifndef