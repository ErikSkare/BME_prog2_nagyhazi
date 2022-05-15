/**
 * \file diakjegy.cpp
 *
 * A diakjegy.hpp-hez tartozó definíciók.
 */

#include "diakjegy.h"

void DiakJegy::exec(const Utas& utas) {
    if(!utas.hasSzemelyIg() || !utas.hasDiakIg())
        throw ErvenyesitesiHiba(false, !utas.hasSzemelyIg(), !utas.hasDiakIg());
    setHasznalhato(false);
}

void DiakJegy::kiir(std::ostream& os) const {
    os << (*this);
}

std::istream& operator>>(std::istream& is, DiakJegy& jegy) {
    uint kedvezmeny;
    is >> (Jegy&) jegy >> kedvezmeny;
    jegy.setKedvezmeny(kedvezmeny);
    return is;
}

std::ostream& operator<<(std::ostream& os, const DiakJegy& jegy) {
    os << DIAKJEGY << " " << (Jegy&) jegy << " " << jegy.getKedvezmeny();
    return os;
}
