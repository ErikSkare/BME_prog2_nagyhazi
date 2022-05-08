#ifndef DATUM_HPP
#define DATUM_HPP

/**
 * \file datum.hpp
 *
 * Datum osztály deklarációja
 */

using uint = unsigned int;

class Datum {
    uint ev, honap, nap, ora, perc;

public:
    /// Konstruktor
    Datum(uint ev, uint honap, uint nap, uint ora, uint perc)
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

    /// virtuális destruktor
    virtual ~Datum() { }
};

#endif
