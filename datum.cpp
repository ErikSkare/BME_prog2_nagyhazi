/**
 * \file datum.cpp
 *
 * A datum.hpp-hez tartozó definíciók.
 */

#include "datum.hpp"

std::istream& operator>>(std::istream& is, Datum& datum) {
    uint ev, honap, nap, ora, perc;
    is >> ev >> honap >> nap >> ora >> perc;
    datum.setEv(ev);
    datum.setHonap(honap);
    datum.setNap(nap);
    datum.setOra(ora);
    datum.setPerc(perc);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Datum& datum) {
    os << datum.getEv() << " " << datum.getHonap() << " " << datum.getNap() << " "
       << datum.getOra() << " " << datum.getPerc();
    return os;
}
