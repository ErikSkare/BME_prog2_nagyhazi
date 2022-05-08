#ifndef VONAT_HPP
#define VONAT_HPP

/**
 * \file datum.hpp
 *
 * Vonat oszt�ly, hozz� tartoz� hibaoszt�lyok, predik�tumok deklar�ci�ja
 */

using uint = unsigned int;

#include <iostream>
#include <exception>
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
    uint azonosito; ///> a vonat egyedi azonos�t�ja, a vonatok heterog�n kollekci�ba csak egyedi azonos�t�j� vonatok ker�lhetnek!
    HeteroStore<Jegy> jegyek; ///> a vonathoz tartoz� jegyek, �ket lehet �rv�nyes�teni az adott vonaton.
    string indAllomas, erkAllomas; ///> indul�si �llom�s, �rkez�si �llom�s
    Datum indIdo, erkIdo; ///> indul�si id�, �rkez�si id�

public:
    /// Konstruktor
    /// @param ia - indul�si �llom�s
    /// @param ii - indul�si id�
    /// @param ea - �rkez�si �llom�s
    /// @param ei - �rkez�si id�
    /// A default �rt�kek �rv�nytelen vonatnak sz�m�tanak, a beolvas�shoz kellenek,
    /// hogy legyen default konstruktor.
    Vonat(string ia = "", Datum ii = {0, 0, 0, 0, 0}, string ea = "", Datum ei = {0, 0, 0, 0, 0})
        : indAllomas(ia), erkAllomas(ea), indIdo(ii), erkIdo(ei) { }

    /// azonosito getter met�dusa
    /// @return azonosito
    inline uint getAzonosito() const { return azonosito; }

    /// azonosito setter met�dusa
    /// @param val - az �j �rt�k
    inline void setAzonosito(uint val) { azonosito = val; }

    /// indAllomas getter met�dusa
    /// @return indAllomas
    inline string getIndAllomas() const { return indAllomas; }

    /// indAllomas setter met�dusa
    /// @param val - az �j �rt�k
    inline void setIndAllomas(string val) { indAllomas = val; }

    /// erkAllomas getter met�dusa
    /// @return erkAllomas
    inline string getErkAllomas() const { return erkAllomas; }

    /// erkAllomas setter met�dusa
    /// @param val - az �j �rt�k
    inline void setErkAllomas(string val) { erkAllomas = val; }

    /// indIdo getter met�dusa
    /// @return indIdo
    inline Datum getIndIdo() const { return indIdo; }

    /// indIdo setter met�dusa
    /// @param val - az �j �rt�k
    inline void setIndIdo(Datum val) { indIdo = val; }

    /// erkIdo getter met�dusa
    /// @return erkIdo
    inline Datum getErkIdo() const { return erkIdo; }

    /// erkIdo setter met�dusa
    /// @param val - az �j �rt�k
    inline void setErkIdo(Datum val) { erkIdo = val; }

    /// hozz�ad egy jegyet a vonathoz, hogy k�s�bb �rv�nyes�teni lehessen
    /// @param jegy - a hozz�adand� jegy
    /// ha m�r foglalt a hely, akkor kiv�tel keletkezik, �s felszabad�t�dik a jegy!
    void jegyHozzaad(Jegy* jegy);

    /// beolvassa a vonathoz tartoz� jegyeket egy streamr�l.
    /// @param is - a stream, ahonnan a beolvas�s t�rt�nik.
    void jegyekBeolvas(std::istream& is);

    /// megkeres egy a vonathoz tartoz� jegyet
    /// @param ksz - kocsisz�m
    /// @param hsz - helysz�m
    /// @return a megtal�lt jegyre mutat� pointer, vagy NULL, ha nem tal�lt semmit
    Jegy* jegyKeres(uint ksz, uint hsz) const;

    /// virtu�lis destruktor
    virtual ~Vonat() { }
};

/// Egy vonat adatait beolvas� oper�tor.
/// @param is - a stream, ahonnan a beolvas�s lesz.
/// @param vonat - a vonat, ahova az adatokat be�rjuk.
/// @return a stream.
std::istream& operator>>(std::istream& is, Vonat& vonat);

/// Egy vonat adatait ki�r� oper�tor.
/// @param os - a stream, ahova a ki�r�s lesz.
/// @param vonat - a vonat, aminek az adatait ki�rjuk.
/// @return a stream.
std::ostream& operator<<(std::ostream& os, const Vonat& vonat);

/// Beolvas sok vonatot.
/// @param is - a stream, ahonnan a beolvas�s lesz.
/// @param vonatok - a vonatok heterog�n kollekci�, ahova az adatokat be�rjuk.
/// @return a stream
std::istream& operator>>(std::istream& is, HeteroStore<Vonat>& vonatok);

/// Ki�r sok vonatot.
/// @param os - a stream, ahova a ki�r�s lesz.
/// @param vonatok - a vonatok heterog�n kollekci�, aminek az adatait ki�rjuk.
/// @return a stream
std::ostream& operator<<(std::ostream& os, const HeteroStore<Vonat>& vonatok);

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

struct vonatKiir {
    std::ostream& os;

    vonatKiir(std::ostream& os)
        : os(os) { }

    void operator()(Vonat* vonat) { os << *vonat << "\n"; }
};
/// Predik�tumok v�ge

#endif
