#include <iostream>
#include <fstream>
#include "memtrace.h"

using namespace std;

int main()
{
    int *a = new int;
    delete a;
    return 0;
}
