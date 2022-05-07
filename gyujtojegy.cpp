/**
 * \file gyujtojegy.cpp
 *
 * A gyujtojegy.hpp-hez tartozó definíciók.
 */

#include "gyujtojegy.hpp"

void GyujtoJegy::exec(const Utas& utas) {
    if(!utas.hasSzemelyIg())
        throw ErvenyesitesiHiba(false, true, false);
    if(--darab == 0)
        setHasznalhato(false);
}

void GyujtoJegy::kiir(std::ostream& os) const {
    os << (*this);
}

std::istream& operator>>(std::istream& is, GyujtoJegy& jegy) {
    uint darab;
    is >> (Jegy&) jegy >> darab;
    jegy.setDarab(darab);
    return is;
}

std::ostream& operator<<(std::ostream& os, const GyujtoJegy& jegy) {
    os << GYUJTOJEGY << " " << (Jegy&) jegy << " " << jegy.getDarab();
    return os;
}
