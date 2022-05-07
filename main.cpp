#include <iostream>

#include "diakjegy.hpp"

using namespace std;

int main()
{
    DiakJegy jegy(5, 4, 20);
    try {
        jegy.ervenyesit({true, true});
        jegy.ervenyesit({true, true});
    } catch(ErvenyesitesiHiba& hiba) {
        hiba.what(cout);
    }
    return 0;
}
