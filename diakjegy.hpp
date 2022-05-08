#ifndef DIAKJEGY_HPP
#define DIAKJEGY_HPP

/**
 * \file diakjegy.hpp
 *
 * DiakJegy osztály és a hozzá tartozó
 * inline függvények deklarációja.
 */

#include "jegy.hpp"

class DiakJegy : public Jegy {
    uint kedvezmeny; ///< A jegyhez tartozó kedvezmény, megjelenítéshez. (százalékban)

public:
    DiakJegy(Vonat* j = NULL, uint ksz = 0, uint hsz = 0, uint kedvezmeny = 0)
        : Jegy(j, ksz, hsz), kedvezmeny(kedvezmeny) { }

    /// kedvezmeny getter metódusa
    /// @return kedvezmeny
    inline uint getKedvezmeny() const { return kedvezmeny; }

    /// kedvezmeny setter metódusa
    /// @param val - az új érték
    inline void setKedvezmeny(uint val) { kedvezmeny = val; }

    void kiir(std::ostream& os) const;

    virtual ~DiakJegy() { }

protected:
    void exec(const Utas& utas);
};

std::istream& operator>>(std::istream& is, DiakJegy& jegy);

std::ostream& operator<<(std::ostream& os, const DiakJegy& jegy);

#endif
