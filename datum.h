#ifndef DATUM_H
#define DATUM_H

/**
 * \file datum.h
 *
 * Datum osztály deklarációja
 */

using uint = unsigned int;

#include <istream>
#include <ostream>

class Datum {
    uint ev, honap, nap, ora, perc;

public:
    /// Konstruktor
    /// A default értékek érvénytelen datumnak számítanak, a beolvasáshoz kellenek,
    /// hogy legyen default konstruktor.
    Datum(uint ev = 0, uint honap = 0, uint nap = 0, uint ora = 0, uint perc = 0)
        : ev(ev), honap(honap), nap(nap), ora(ora), perc(perc) { }

    /// ev getter metódusa
    /// @return ev
    inline uint getEv() const { return ev; }

    /// ev setter metódusa
    /// @param val - az új érték
    inline void setEv(uint val) { ev = val; }

    /// honap getter metódusa
    /// @return honap
    inline uint getHonap() const { return honap; }

    /// honap setter metódusa
    /// @param val - az új érték
    inline void setHonap(uint val) { honap = val; }

    /// nap getter metódusa
    /// @return nap
    inline uint getNap() const { return nap; }

    /// nap setter metódusa
    /// @param val - az új érték
    inline void setNap(uint val) { nap = val; }

    /// ora getter metódusa
    /// @return ora
    inline uint getOra() const { return ora; }

    /// ora setter metódusa
    /// @param val - az új érték
    inline void setOra(uint val) { ora = val; }

    /// perc getter metódusa
    /// @return perc
    inline uint getPerc() const { return perc; }

    /// perc setter metódusa
    /// @param val - az új érték
    inline void setPerc(uint val) { perc = val; }

    bool operator==(const Datum& masik) const;

    /// virtuális destruktor
    virtual ~Datum() { }
};

/// Egy datum adatait beolvasó operátor.
/// @param is - a stream, ahonnan a beolvasás lesz.
/// @param datum - a datum, ahova a beírás lesz.
/// @return a stream.
std::istream& operator>>(std::istream& is, Datum& datum);

/// Egy datum adatait kiíró operátor.
/// @param os - a stream, ahova a kiírás lesz.
/// @param datum - a datum, aminek az adatait kiírjuk.
/// @return a stream.
std::ostream& operator<<(std::ostream& os, const Datum& datum);

#endif
