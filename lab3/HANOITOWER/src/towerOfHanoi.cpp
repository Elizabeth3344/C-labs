#include <iostream>
#include <list>
using namespace std;

void towerOfHanoi(int n, char from_rod, char to_rod, char aux_rod, list<string> *steps)
{
    if (n == 0)
    {
        return;
    }

    towerOfHanoi(n - 1, from_rod, aux_rod, to_rod, steps);

    steps->push_back("Move disk " + to_string(n) + " from rod " + from_rod + " to rod " + to_rod + "\n");

    towerOfHanoi(n - 1, aux_rod, to_rod, from_rod, steps);
}