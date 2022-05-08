#include <iostream>

#include "gyujtojegy.hpp"

using namespace std;

int main()
{
    GyujtoJegy jegy(5, 4, 2);
    try {
        jegy.ervenyesit({true, true});
        jegy.ervenyesit({true, true});
    } catch(ErvenyesitesiHiba& hiba) {
        hiba.what(cout);
    }
    return 0;
}
