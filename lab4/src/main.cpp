#include "../inc/sequentialСalc.h"
#include "../inc/sequentialСalcOpt.h"
#include "../inc/threadsCalc.h"
#include "../inc/processesCalc.h"

int main()
{
    sequentialСalc(10'000);
    sequentialСalc(100'000);
    sequentialСalcOpt(10'000);
    sequentialСalcOpt(100'000);
    threadsCalc(10'000);
    threadsCalc(100'000);
    processesCalc(10'000);
    processesCalc(100'000);
    return 0;
}