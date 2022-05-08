#ifndef GYUJTOJEGY_HPP
#define GYUJTOJEGY_HPP

/**
 * \file gyujtojegy.hpp
 *
 * GyujtoJegy oszt�ly �s a hozz� tartoz�
 * inline f�ggv�nyek deklar�ci�ja.
 */

#include "jegy.hpp"

class GyujtoJegy : public Jegy {
    uint darab; ///> ah�nyszor m�g felhaszn�lhat� a jegy.

public:
    GyujtoJegy(Vonat* j = NULL, uint ksz = 0, uint hsz = 0, uint darab = 0)
        : Jegy(j, ksz, hsz), darab(darab) { }

    /// darab getter met�dusa
    /// @return darab
    inline uint getDarab() const { return darab; }

    /// darab setter met�dusa
    /// @param val - az �j �rt�k
    inline void setDarab(uint val) { darab = val; }

    void kiir(std::ostream& os) const;

    virtual ~GyujtoJegy() { }

protected:
    void exec(const Utas& utas);
};

std::istream& operator>>(std::istream& is, GyujtoJegy& jegy);

std::ostream& operator<<(std::ostream& os, const GyujtoJegy& jegy);

#endif
