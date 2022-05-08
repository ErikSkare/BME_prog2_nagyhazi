#include <iostream>
#include <fstream>
#include "vonat.hpp"

using namespace std;

int main()
{
    ifstream fs("vonatok.txt");
    HeteroStore<Vonat> vonatok;
    fs >> vonatok;
    fs.close();

    vonatok.bejar(jegyekBeolvasFajlbol("jegyek.txt"));

    vonatok.keres(vonatKeresByAzon(0))->jegyTorol(vonatok.keres(vonatKeresByAzon(0))->jegyKeres(5, 4));
    Jegy* jegy = vonatok.keres(vonatKeresByAzon(0))->jegyKeres(5, 4);
    if(jegy == NULL)
        cout<<"1";
    return 0;
}
