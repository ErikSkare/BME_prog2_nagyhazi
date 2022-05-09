/**
 * \file jegy.cpp
 *
 * A jegy.hpp-hez tartozó definíciók.
 */

#include "jegy.hpp"
#include "vonat.hpp"

ErvenyesitesiHiba::ErvenyesitesiHiba(bool nh, bool nsz, bool nd) {
    uzenet = std::string("Sikertelen ervenyesites: \n");
    if(nh) uzenet += std::string("  - A jegy mar nem hasznalhato!\n");
    if(nsz) uzenet += std::string("  - Az utasnal nincs szemelyi!\n");
    if(nd) uzenet += std::string("  - Az utasnal nincs diak!\n");
}

const char* ErvenyesitesiHiba::what() const throw() {
    return uzenet.c_str();
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
