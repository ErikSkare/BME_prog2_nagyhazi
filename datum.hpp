#ifndef DATUM_HPP
#define DATUM_HPP

/**
 * \file datum.hpp
 *
 * Datum oszt�ly deklar�ci�ja
 */

using uint = unsigned int;

class Datum {
    uint ev, honap, nap, ora, perc;

public:
    /// Konstruktor
    Datum(uint ev, uint honap, uint nap, uint ora, uint perc)
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

    /// virtu�lis destruktor
    virtual ~Datum() { }
};

#endif
