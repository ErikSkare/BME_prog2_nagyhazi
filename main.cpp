#include <iostream>
#include <fstream>
#include "memtrace.h"
#include "gyujtojegy.hpp"
#include "vonat.hpp"

using namespace std;

int main()
{
    ifstream fs("vonatok.txt");
    HeteroStore<Vonat> vonatok;
    fs >> vonatok;
    fs.close();

    vonatok.bejar(jegyekBeolvasFajlbol("jegyek.txt"));

    Vonat* vonat = vonatok.keres(vonatKeresByAzon(0));
    try {
        vonat->jegyHozzaad(new GyujtoJegy(vonat, 5, 5, 2));
    } catch(FoglaltHiba&) {
        std::cout << "hello";
    }
    vonat->jegyekKiir(cout);
    return 0;
}
