#ifndef DATUM_H
#define DATUM_H

/**
 * \file datum.h
 *
 * Datum oszt�ly deklar�ci�ja
 */

using uint = unsigned int;

#include <istream>
#include <ostream>

class Datum {
    uint ev, honap, nap, ora, perc;

public:
    /// Konstruktor
    /// A default �rt�kek �rv�nytelen datumnak sz�m�tanak, a beolvas�shoz kellenek,
    /// hogy legyen default konstruktor.
    Datum(uint ev = 0, uint honap = 0, uint nap = 0, uint ora = 0, uint perc = 0)
        : ev(ev), honap(honap), nap(nap), ora(ora), perc(perc) { }

    /// ev getter met�dusa
    /// @return ev
    inline uint getEv() const { return ev; }

    /// ev setter met�dusa
    /// @param val - az �j �rt�k
    inline void setEv(uint val) { ev = val; }

    /// honap getter met�dusa
    /// @return honap
    inline uint getHonap() const { return honap; }

    /// honap setter met�dusa
    /// @param val - az �j �rt�k
    inline void setHonap(uint val) { honap = val; }

    /// nap getter met�dusa
    /// @return nap
    inline uint getNap() const { return nap; }

    /// nap setter met�dusa
    /// @param val - az �j �rt�k
    inline void setNap(uint val) { nap = val; }

    /// ora getter met�dusa
    /// @return ora
    inline uint getOra() const { return ora; }

    /// ora setter met�dusa
    /// @param val - az �j �rt�k
    inline void setOra(uint val) { ora = val; }

    /// perc getter met�dusa
    /// @return perc
    inline uint getPerc() const { return perc; }

    /// perc setter met�dusa
    /// @param val - az �j �rt�k
    inline void setPerc(uint val) { perc = val; }

    bool operator==(const Datum& masik) const;

    /// virtu�lis destruktor
    virtual ~Datum() { }
};

/// Egy datum adatait beolvas� oper�tor.
/// @param is - a stream, ahonnan a beolvas�s lesz.
/// @param datum - a datum, ahova a be�r�s lesz.
/// @return a stream.
std::istream& operator>>(std::istream& is, Datum& datum);

/// Egy datum adatait ki�r� oper�tor.
/// @param os - a stream, ahova a ki�r�s lesz.
/// @param datum - a datum, aminek az adatait ki�rjuk.
/// @return a stream.
std::ostream& operator<<(std::ostream& os, const Datum& datum);

#endif
