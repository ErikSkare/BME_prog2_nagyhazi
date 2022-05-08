#ifndef DIAKJEGY_HPP
#define DIAKJEGY_HPP

/**
 * \file diakjegy.hpp
 *
 * DiakJegy oszt�ly �s a hozz� tartoz�
 * inline f�ggv�nyek deklar�ci�ja.
 */

#include "jegy.hpp"

class DiakJegy : public Jegy {
    uint kedvezmeny; ///< A jegyhez tartoz� kedvezm�ny, megjelen�t�shez. (sz�zal�kban)

public:
    DiakJegy(Vonat* j = NULL, uint ksz = 0, uint hsz = 0, uint kedvezmeny = 0)
        : Jegy(j, ksz, hsz), kedvezmeny(kedvezmeny) { }

    /// kedvezmeny getter met�dusa
    /// @return kedvezmeny
    inline uint getKedvezmeny() const { return kedvezmeny; }

    /// kedvezmeny setter met�dusa
    /// @param val - az �j �rt�k
    inline void setKedvezmeny(uint val) { kedvezmeny = val; }

    void kiir(std::ostream& os) const;

    virtual ~DiakJegy() { }

protected:
    void exec(const Utas& utas);
};

std::istream& operator>>(std::istream& is, DiakJegy& jegy);

std::ostream& operator<<(std::ostream& os, const DiakJegy& jegy);

#endif
