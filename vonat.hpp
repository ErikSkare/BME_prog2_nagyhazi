#ifndef VONAT_HPP
#define VONAT_HPP

/**
 * \file datum.hpp
 *
 * Vonat osztály, hozzá tartozó hibaosztályok, predikátumok deklarációja
 */

using uint = unsigned int;

#include <iostream>
#include <exception>
#include <fstream>
#include "heterostore.hpp"
#include "heterostore.cpp"
#include "jegy.hpp"
#include "datum.hpp"

using std::string;

class FoglaltHiba : std::exception {
    uint kocsiSzam, helySzam;

public:
    FoglaltHiba(uint ksz, uint hsz)
        : kocsiSzam(ksz), helySzam(hsz) { }

    virtual void what(std::ostream& os) { os << "A(z) " << kocsiSzam << ". kocsi " << helySzam << ". helye mar foglalt!\n"; }

    virtual ~FoglaltHiba() { }
};

class RosszVonatHiba : std::exception {
public:
    virtual void what(std::ostream& os) { os << "Ehhez a vonathoz nem lehet hozzaadni a jegyet!\n"; }

    virtual ~RosszVonatHiba() { }
};

class Vonat {
    uint azonosito; ///> a vonat egyedi azonosítója, a vonatok heterogén kollekcióba csak egyedi azonosítójú vonatok kerülhetnek!
    HeteroStore<Jegy> jegyek; ///> a vonathoz tartozó jegyek, õket lehet érvényesíteni az adott vonaton.
    string indAllomas, erkAllomas; ///> indulási állomás, érkezési állomás
    Datum indIdo, erkIdo; ///> indulási idõ, érkezési idõ

public:
    /// Konstruktor
    /// @param az - azonosító
    /// @param ia - indulási állomás
    /// @param ii - indulási idõ
    /// @param ea - érkezési állomás
    /// @param ei - érkezési idõ
    /// A default értékek érvénytelen vonatnak számítanak, a beolvasáshoz kellenek,
    /// hogy legyen default konstruktor.
    Vonat(uint az = 0, string ia = "", Datum ii = {0, 0, 0, 0, 0}, string ea = "", Datum ei = {0, 0, 0, 0, 0})
        : azonosito(az), indAllomas(ia), erkAllomas(ea), indIdo(ii), erkIdo(ei) { }

    /// azonosito getter metódusa
    /// @return azonosito
    inline uint getAzonosito() const { return azonosito; }

    /// azonosito setter metódusa
    /// @param val - az új érték
    inline void setAzonosito(uint val) { azonosito = val; }

    /// indAllomas getter metódusa
    /// @return indAllomas
    inline string getIndAllomas() const { return indAllomas; }

    /// indAllomas setter metódusa
    /// @param val - az új érték
    inline void setIndAllomas(string val) { indAllomas = val; }

    /// erkAllomas getter metódusa
    /// @return erkAllomas
    inline string getErkAllomas() const { return erkAllomas; }

    /// erkAllomas setter metódusa
    /// @param val - az új érték
    inline void setErkAllomas(string val) { erkAllomas = val; }

    /// indIdo getter metódusa
    /// @return indIdo
    inline Datum getIndIdo() const { return indIdo; }

    /// indIdo setter metódusa
    /// @param val - az új érték
    inline void setIndIdo(Datum val) { indIdo = val; }

    /// erkIdo getter metódusa
    /// @return erkIdo
    inline Datum getErkIdo() const { return erkIdo; }

    /// erkIdo setter metódusa
    /// @param val - az új érték
    inline void setErkIdo(Datum val) { erkIdo = val; }

    /// hozzáad egy jegyet a vonathoz, hogy késõbb érvényesíteni lehessen
    /// @param jegy - a hozzáadandó jegyre mutató pointer
    /// ha már foglalt a hely, akkor kivétel keletkezik, és felszabadítódik a jegy!
    void jegyHozzaad(Jegy* jegy);

    /// kitörli a megadott jegyet a vonat jegyei közül, ha az megtalálható
    /// @param jegy - a törlendõ jegyre mutató pointer
    void jegyTorol(Jegy* jegy);

    /// beolvassa a vonathoz tartozó jegyeket egy streamról.
    /// @param is - a stream, ahonnan a beolvasás történik.
    void jegyekBeolvas(std::istream& is);

    /// kiírja a vonathoz tartozó jegyeket egy streamre.
    /// @param os - a stream, ahova a kiírás történik.
    void jegyekKiir(std::ostream& os) const;

    /// megkeres egy a vonathoz tartozó jegyet
    /// @param ksz - kocsiszám
    /// @param hsz - helyszám
    /// @return a megtalált jegyre mutató pointer, vagy NULL, ha nem talált semmit
    Jegy* jegyKeres(uint ksz, uint hsz) const;

    /// virtuális destruktor
    virtual ~Vonat() { }
};

/// Egy vonat adatait beolvasó operátor.
/// @param is - a stream, ahonnan a beolvasás lesz.
/// @param vonat - a vonat, ahova az adatokat beírjuk.
/// @return a stream.
std::istream& operator>>(std::istream& is, Vonat& vonat);

/// Egy vonat adatait kiíró operátor.
/// @param os - a stream, ahova a kiírás lesz.
/// @param vonat - a vonat, aminek az adatait kiírjuk.
/// @return a stream.
std::ostream& operator<<(std::ostream& os, const Vonat& vonat);

/// Beolvas sok vonatot.
/// @param is - a stream, ahonnan a beolvasás lesz.
/// @param vonatok - a vonatok heterogén kollekció, ahova az adatokat beírjuk.
/// @return a stream
std::istream& operator>>(std::istream& is, HeteroStore<Vonat>& vonatok);

/// Kiír sok vonatot.
/// @param os - a stream, ahova a kiírás lesz.
/// @param vonatok - a vonatok heterogén kollekció, aminek az adatait kiírjuk.
/// @return a stream
std::ostream& operator<<(std::ostream& os, const HeteroStore<Vonat>& vonatok);

/// Predikátumok kezdete
struct jegyekBeolvasStreamrol {
    std::istream& is;

    jegyekBeolvasStreamrol(std::istream& is)
        : is(is) { }

    void operator()(Vonat* vonat) {
        is.clear();
        is.seekg(0, std::ios::beg);
        vonat->jegyekBeolvas(is);
    }
};

struct jegyekKiirStreamre {
    std::ostream& os;

    jegyekKiirStreamre(std::ostream& os)
        : os(os) { }

    void operator()(Vonat* vonat) { vonat->jegyekKiir(os); }
};

struct vonatKeresByAzon {
    uint azon;

    vonatKeresByAzon(uint azon)
        : azon(azon) { }

    bool operator()(Vonat* vonat) { return vonat->getAzonosito() == azon; }
};

struct vonatKiir {
    std::ostream& os;

    vonatKiir(std::ostream& os)
        : os(os) { }

    void operator()(Vonat* vonat) { os << *vonat << "\n"; }
};
/// Predikátumok vége

#endif
