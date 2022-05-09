/**
 * \file teljesjegy.cpp
 *
 * A teljesjegy.hpp-hez tartozó definíciók.
 */

#include "teljesjegy.hpp"

void TeljesJegy::exec(const Utas& utas) {
    if(!utas.hasSzemelyIg())
        throw ErvenyesitesiHiba(false, true, false);
    setHasznalhato(false);
}

void TeljesJegy::kiir(std::ostream& os) const {
    os << (*this);
}

std::istream& operator>>(std::istream& is, TeljesJegy& jegy) {
    is >> (Jegy&) jegy;
    return is;
}

std::ostream& operator<<(std::ostream& os, const TeljesJegy& jegy) {
    os << TELJESJEGY << " " << (Jegy&) jegy;
    return os;
}
