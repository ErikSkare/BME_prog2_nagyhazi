/**
 * \file jegy.cpp
 *
 * A jegy.hpp-hez tartozó definíciók.
 */

#include "jegy.hpp"
#include "vonat.hpp"

void ErvenyesitesiHiba::what(std::ostream& os) {
    os << "Sikertelen ervenyesites: \n";
    if(nemHasznalhato)
        os << "  - A jegy mar nem hasznalhato!\n";
    if(nincsSzemelyi)
        os << "  - Az utasnal nincs szemelyi!\n";
    if(nincsDiak)
        os << "  - Az utasnal nincs diak!\n";
}

void Jegy::ervenyesit(const Utas& utas) {
    if(!hasznalhato)
        throw ErvenyesitesiHiba(true, false, false);
    exec(utas);
}

bool Jegy::operator==(const Jegy& masik) const {
    return kocsiSzam == masik.getKocsiSzam() && helySzam == masik.getHelySzam();
}

std::istream& operator>>(std::istream& is, Jegy& jegy) {
    uint kocsiSzam, helySzam;
    is >> kocsiSzam >> helySzam;
    jegy.setKocsiSzam(kocsiSzam);
    jegy.setHelySzam(helySzam);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Jegy& jegy) {
    os << jegy.getJarat()->getAzonosito() << " " << jegy.getKocsiSzam() << " " << jegy.getHelySzam();
    return os;
}
