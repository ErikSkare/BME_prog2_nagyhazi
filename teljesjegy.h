#ifndef TELJESJEGY_H
#define TELJESJEGY_H

/**
 * \file teljesjegy.h
 *
 * TeljesJegy oszt�ly �s a hozz� tartoz�
 * inline f�ggv�nyek deklar�ci�ja.
 */

#include "jegy.h"

class TeljesJegy : public Jegy {
public:
    TeljesJegy(Vonat* j = NULL, uint ksz = 0, uint hsz = 0)
        : Jegy(j, ksz, hsz) { }

    void kiir(std::ostream& os) const;

    virtual ~TeljesJegy() { }

protected:
    void exec(const Utas& utas);
};

std::istream& operator>>(std::istream& is, TeljesJegy& jegy);

std::ostream& operator<<(std::ostream& os, const TeljesJegy& jegy);

#endif
