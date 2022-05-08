#ifndef GYUJTOJEGY_HPP
#define GYUJTOJEGY_HPP

/**
 * \file gyujtojegy.hpp
 *
 * GyujtoJegy osztály és a hozzá tartozó
 * inline függvények deklarációja.
 */

#include "jegy.hpp"

class GyujtoJegy : public Jegy {
    uint darab; ///> ahányszor még felhasználható a jegy.

public:
    GyujtoJegy(Vonat* j = NULL, uint ksz = 0, uint hsz = 0, uint darab = 0)
        : Jegy(j, ksz, hsz), darab(darab) { }

    /// darab getter metódusa
    /// @return darab
    inline uint getDarab() const { return darab; }

    /// darab setter metódusa
    /// @param val - az új érték
    inline void setDarab(uint val) { darab = val; }

    void kiir(std::ostream& os) const;

    virtual ~GyujtoJegy() { }

protected:
    void exec(const Utas& utas);
};

std::istream& operator>>(std::istream& is, GyujtoJegy& jegy);

std::ostream& operator<<(std::ostream& os, const GyujtoJegy& jegy);

#endif
