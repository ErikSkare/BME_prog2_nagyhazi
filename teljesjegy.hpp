#ifndef TELJESJEGY_HPP
#define TELJESJEGY_HPP

/**
 * \file teljesjegy.hpp
 *
 * TeljesJegy osztály és a hozzá tartozó
 * inline függvények deklarációja.
 */

#include "jegy.hpp"

class TeljesJegy : public Jegy {
public:
    TeljesJegy(uint ksz = 0, uint hsz = 0)
        : Jegy(ksz, hsz) { }

    void kiir(std::ostream& os) const;

    virtual ~TeljesJegy() { }

protected:
    void exec(const Utas& utas);
};

std::istream& operator>>(std::istream& is, TeljesJegy& jegy);

std::ostream& operator<<(std::ostream& os, const TeljesJegy& jegy);

#endif
