#ifndef JEGY_HPP
#define JEGY_HPP

/**
 * \file jegy.hpp
 *
 * Jegy absztrakt osztály, hozzátartozó hiba osztályok,
 * inline függvények deklarációja.
 */

using uint = unsigned int;

#include <exception>
#include <ostream>
#include <istream>
#include "utas.hpp"

/// Enum a jegyek azonosításához a beolvasásnál.
enum Jegyek {
    TELJESJEGY = 1,
    DIAKJEGY = 2,
    GYUJTOJEGY = 3
};

class ErvenyesitesiHiba : std::exception {
    bool nemHasznalhato; ///< Az utasnál lévõ jegy már nem használható.
    bool nincsSzemelyi; ///< Nincs az utasnál személyigazolvány.
    bool nincsDiak; ///< Nincs az utasnál diákigazolvány.

public:
    /// Konstruktor
    /// @param nh - nemHasznalhato
    /// @param nsz - nincsSzemelyi
    /// @param nd - nincsDiak
    ErvenyesitesiHiba(bool nh, bool nsz, bool nd)
        : nemHasznalhato(nh), nincsSzemelyi(nsz), nincsDiak(nd) { }

    /// a hibát kiíró metódus
    /// @param os - a stream, amire a kiírás történik.
    virtual void what(std::ostream& os);

    /// virtuális destruktor
    virtual ~ErvenyesitesiHiba() { }
};

class Jegy {
    uint kocsiSzam; ///< A vonat kocsijának száma, ahova a jegy szól.
    uint helySzam; ///< A kocsin belüli hely száma, ahova a jegy szól.
    bool hasznalhato; ///< Érvényesítésnél van szerepe. (kezdetben igaz)

public:
    /// Konstruktor
    /// @param ksz - kocsiszám
    /// @param hsz - helyszám
    /// A default értékek érvénytelen jegynek számítanak, a beolvasáshoz kellenek,
    /// hogy legyen default konstruktor.
    Jegy(uint ksz = 0, uint hsz = 0)
        : kocsiSzam(ksz), helySzam(hsz), hasznalhato(true) { }

    /// kocsiSzam getter metódusa
    /// @return kocsiSzam
    inline uint getKocsiSzam() const { return kocsiSzam; }

    /// kocsiSzam setter metódusa
    /// @param val - az új érték
    inline void setKocsiSzam(uint val) { kocsiSzam = val; }

    /// helySzam getter metódusa
    /// @return helySzam
    inline uint getHelySzam() const { return helySzam; }

    /// helySzam setter metódusa
    /// @param val - az új érték
    inline void setHelySzam(uint val) { helySzam = val; }

    /// hasznalhato getter metódusa
    /// @return hasznalhato
    inline bool isHasznalhato() const { return hasznalhato; }

    /// érvényesítõ metódus
    /// @param utas - az utas, aki érvényesíti a jegyet.
    /// ErvenyesitesiHiba-t dobhat, ha valami probléma van.
    void ervenyesit(const Utas& utas);

    /// egyenlõséget vizsgáló operátor
    /// @param masik - a másik jegy, amivel hasonlítani akarunk.
    /// @return igaz, ha a vonat, a kocsiSzám és a helySzám megegyezik.
    bool operator==(const Jegy& masik) const;

    /// kiir metódus, heterogén kollekció miatt.
    /// @param os - a stream, amire a kiírás történik.
    virtual void kiir(std::ostream& os) const = 0;

    /// virtuális destruktor
    virtual ~Jegy() { }

protected:
    /// hasznalhato setter metódusa
    /// @param val - az új érték
    inline void setHasznalhato(bool val) { hasznalhato = val; }

    /// a jegy kritériumait ellenõrzõ metódus
    /// @param utas - az utas, aki érvényesíti a jegyet.
    /// ErvenyesitesiHiba-t dobhat, ha valamelyik kritérium nem teljesül.
    virtual void exec(const Utas& utas) = 0;
};

/// egy jegy adatait beolvasó operátor
/// @param is - a stream, amirõl az olvasás történik.
/// @param jegy - a jegy, amibe az adatok beírása történik.
/// @return a stream.
std::istream& operator>>(std::istream& is, Jegy& jegy);

/// egy jegy adatait kiíró operátor
/// @param os - a stream, ahová a kiírás történik.
/// @param jegy - a jegy, aminek az adatait kiírjuk.
/// @return a stream.
std::ostream& operator<<(std::ostream& os, const Jegy& jegy);

#endif
