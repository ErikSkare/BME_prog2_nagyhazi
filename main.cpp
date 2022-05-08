#include <iostream>
#include <fstream>
#include "vonat.hpp"
#include "memtrace.h"

using namespace std;

int main()
{
    // beolvasás
    HeteroStore<Vonat> vonatok;
    ifstream fs1("vonatok.txt");
    if(fs1.is_open()) {
        fs1 >> vonatok;
        fs1.close();
    }
    ifstream fs2("jegyek.txt");
    if(fs2.is_open()) {
        vonatok.bejar(jegyekBeolvasStreamrol(fs2));
        fs2.close();
    }
    return 0;
}
