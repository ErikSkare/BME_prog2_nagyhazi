#ifndef JEGY_H
#define JEGY_H

/**
 * \file jegy.h
 *
 * Jegy absztrakt oszt�ly, hozz�tartoz� hiba oszt�lyok, predik�tumok,
 * inline f�ggv�nyek deklar�ci�ja.
 */

using uint = unsigned int;

#include <exception>
#include <ostream>
#include <istream>
#include "utas.h"

class Vonat;

/// Enum a jegyek azonos�t�s�hoz a beolvas�sn�l.
enum Jegyek {
    TELJESJEGY = 1,
    DIAKJEGY = 2,
    GYUJTOJEGY = 3
};

class ErvenyesitesiHiba : std::exception {
    std::string uzenet;

public:
    /// Konstruktor
    /// @param nh - nem haszn�lhat�
    /// @param nsz - nincs szem�lyi
    /// @param nd - nincs di�k
    ErvenyesitesiHiba(bool nh, bool nsz, bool nd);

    virtual const char* what() const throw();

    /// virtu�lis destruktor
    virtual ~ErvenyesitesiHiba() { }
};

class Jegy {
    Vonat* jarat;
    uint kocsiSzam; ///< A vonat kocsij�nak sz�ma, ahova a jegy sz�l.
    uint helySzam; ///< A kocsin bel�li hely sz�ma, ahova a jegy sz�l.
    bool hasznalhato; ///< �rv�nyes�t�sn�l van szerepe. (kezdetben igaz)

public:
    /// Konstruktor
    /// @param ksz - kocsisz�m
    /// @param hsz - helysz�m
    /// @param j - j�rat
    /// A default �rt�kek �rv�nytelen jegynek sz�m�tanak, a beolvas�shoz kellenek,
    /// hogy legyen default konstruktor.
    Jegy(Vonat* j = NULL, uint ksz = 0, uint hsz = 0)
        : jarat(j), kocsiSzam(ksz), helySzam(hsz), hasznalhato(true) { }

    /// jarat getter met�dusa
    /// @return jarat
    inline Vonat* getJarat() const { return jarat; }

    /// jarat setter met�dusa
    /// @param val - az �j �rt�k
    inline void setJarat(Vonat* val) { jarat = val; }

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

/// Predik�tumok kezdete
struct jegyKeresByMasikJegy {
    Jegy* alapjan;

    jegyKeresByMasikJegy(Jegy* alapjan)
        : alapjan(alapjan) { }

    bool operator()(Jegy* masik) { return *masik == *alapjan; }
};

struct jegyKeresByPozicio {
    uint kocsiSzam, helySzam;

    jegyKeresByPozicio(uint ksz, uint hsz)
        : kocsiSzam(ksz), helySzam(hsz) { }

    bool operator()(Jegy* jegy) { return kocsiSzam == jegy->getKocsiSzam() && helySzam == jegy->getHelySzam(); }
};

struct jegyKiir {
    std::ostream& os;

    jegyKiir(std::ostream& os)
        : os(os) { }

    void operator()(Jegy* jegy) { jegy->kiir(os); os << "\n"; }
};
/// Predik�tumok v�ge

#endif
