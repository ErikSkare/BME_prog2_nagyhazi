#ifndef JEGY_HPP
#define JEGY_HPP

/**
 * \file jegy.hpp
 *
 * Jegy absztrakt oszt�ly, hozz�tartoz� hiba oszt�lyok,
 * inline f�ggv�nyek deklar�ci�ja.
 */

using uint = unsigned int;

#include <exception>
#include <ostream>
#include <istream>
#include "utas.hpp"

/// Enum a jegyek azonos�t�s�hoz a beolvas�sn�l.
enum Jegyek {
    TELJESJEGY = 1,
    DIAKJEGY = 2,
    GYUJTOJEGY = 3
};

class ErvenyesitesiHiba : std::exception {
    bool nemHasznalhato; ///< Az utasn�l l�v� jegy m�r nem haszn�lhat�.
    bool nincsSzemelyi; ///< Nincs az utasn�l szem�lyigazolv�ny.
    bool nincsDiak; ///< Nincs az utasn�l di�kigazolv�ny.

public:
    /// Konstruktor
    /// @param nh - nemHasznalhato
    /// @param nsz - nincsSzemelyi
    /// @param nd - nincsDiak
    ErvenyesitesiHiba(bool nh, bool nsz, bool nd)
        : nemHasznalhato(nh), nincsSzemelyi(nsz), nincsDiak(nd) { }

    /// a hib�t ki�r� met�dus
    /// @param os - a stream, amire a ki�r�s t�rt�nik.
    virtual void what(std::ostream& os);

    /// virtu�lis destruktor
    virtual ~ErvenyesitesiHiba() { }
};

class Jegy {
    uint kocsiSzam; ///< A vonat kocsij�nak sz�ma, ahova a jegy sz�l.
    uint helySzam; ///< A kocsin bel�li hely sz�ma, ahova a jegy sz�l.
    bool hasznalhato; ///< �rv�nyes�t�sn�l van szerepe. (kezdetben igaz)

public:
    /// Konstruktor
    /// @param ksz - kocsisz�m
    /// @param hsz - helysz�m
    /// A default �rt�kek �rv�nytelen jegynek sz�m�tanak, a beolvas�shoz kellenek,
    /// hogy legyen default konstruktor.
    Jegy(uint ksz = 0, uint hsz = 0)
        : kocsiSzam(ksz), helySzam(hsz), hasznalhato(true) { }

    /// kocsiSzam getter met�dusa
    /// @return kocsiSzam
    inline uint getKocsiSzam() const { return kocsiSzam; }

    /// kocsiSzam setter met�dusa
    /// @param val - az �j �rt�k
    inline void setKocsiSzam(uint val) { kocsiSzam = val; }

    /// helySzam getter met�dusa
    /// @return helySzam
    inline uint getHelySzam() const { return helySzam; }

    /// helySzam setter met�dusa
    /// @param val - az �j �rt�k
    inline void setHelySzam(uint val) { helySzam = val; }

    /// hasznalhato getter met�dusa
    /// @return hasznalhato
    inline bool isHasznalhato() const { return hasznalhato; }

    /// �rv�nyes�t� met�dus
    /// @param utas - az utas, aki �rv�nyes�ti a jegyet.
    /// ErvenyesitesiHiba-t dobhat, ha valami probl�ma van.
    void ervenyesit(const Utas& utas);

    /// egyenl�s�get vizsg�l� oper�tor
    /// @param masik - a m�sik jegy, amivel hasonl�tani akarunk.
    /// @return igaz, ha a vonat, a kocsiSz�m �s a helySz�m megegyezik.
    bool operator==(const Jegy& masik) const;

    /// kiir met�dus, heterog�n kollekci� miatt.
    /// @param os - a stream, amire a ki�r�s t�rt�nik.
    virtual void kiir(std::ostream& os) const = 0;

    /// virtu�lis destruktor
    virtual ~Jegy() { }

protected:
    /// hasznalhato setter met�dusa
    /// @param val - az �j �rt�k
    inline void setHasznalhato(bool val) { hasznalhato = val; }

    /// a jegy krit�riumait ellen�rz� met�dus
    /// @param utas - az utas, aki �rv�nyes�ti a jegyet.
    /// ErvenyesitesiHiba-t dobhat, ha valamelyik krit�rium nem teljes�l.
    virtual void exec(const Utas& utas) = 0;
};

/// egy jegy adatait beolvas� oper�tor
/// @param is - a stream, amir�l az olvas�s t�rt�nik.
/// @param jegy - a jegy, amibe az adatok be�r�sa t�rt�nik.
/// @return a stream.
std::istream& operator>>(std::istream& is, Jegy& jegy);

/// egy jegy adatait ki�r� oper�tor
/// @param os - a stream, ahov� a ki�r�s t�rt�nik.
/// @param jegy - a jegy, aminek az adatait ki�rjuk.
/// @return a stream.
std::ostream& operator<<(std::ostream& os, const Jegy& jegy);

#endif
