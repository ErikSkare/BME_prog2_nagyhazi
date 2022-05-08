#include <iostream>
#include <fstream>
#include "memtrace.h"
#include "vonat.hpp"

using namespace std;

int main()
{
    // beolvasás
    HeteroStore<Vonat> vonatok;
    ifstream be1("vonatok.txt");
    if(be1.is_open()) {
        be1 >> vonatok;
        be1.close();
    }
    ifstream be2("jegyek.txt");
    if(be2.is_open()) {
        vonatok.bejar(jegyekBeolvasStreamrol(be2));
        be2.close();
    }

    // kiírás
    ofstream ki1("vonatok.txt");
    if(!ki1.is_open())
        return 1; //hiba
    vonatok.bejar(vonatKiir(ki1));
    ofstream ki2("jegyek.txt");
    if(!ki2.is_open())
        return 1; //hiba
    vonatok.bejar(jegyekKiirStreamre(ki2));

    return 0;
}
