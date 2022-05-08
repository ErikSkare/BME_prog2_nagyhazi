/**
 * \file vonat.cpp
 *
 * A vonat.hpp-hez tartozó definíciók.
 */

#include "vonat.hpp"
#include "teljesjegy.hpp"
#include "diakjegy.hpp"
#include "gyujtojegy.hpp"

void Vonat::jegyHozzaad(Jegy* jegy) {
    if(jegy->getJarat() != this) {
        delete jegy;
        throw RosszVonatHiba();
    }
    Jegy* talalat = jegyek.keres(jegyKeresByMasikJegy(jegy));
    if(talalat != NULL) {
        delete jegy;
        throw FoglaltHiba(talalat->getKocsiSzam(), talalat->getHelySzam());
    }
    jegyek.hozzaad(jegy);
}

void Vonat::jegyTorol(Jegy* jegy) {
    jegyek.torol(jegyKeresByMasikJegy(jegy));
}

void Vonat::jegyekBeolvas(std::istream& is) {
    uint tipus;
    while(is >> tipus) {
        Jegy* jegy;
        uint vonat_azon;
        is >> vonat_azon;
        switch((Jegyek) tipus) {
            case TELJESJEGY: {
                TeljesJegy* t_jegy = new TeljesJegy();
                is >> *t_jegy;
                jegy = t_jegy;
            } break;
            case DIAKJEGY: {
                DiakJegy* d_jegy = new DiakJegy();
                is >> *d_jegy;
                jegy = d_jegy;
            } break;
            case GYUJTOJEGY: {
                GyujtoJegy* gy_jegy = new GyujtoJegy();
                is >> *gy_jegy;
                jegy = gy_jegy;
            } break;
            default: break;
        }
        if(vonat_azon != azonosito)
            delete jegy;
        else {
            jegy->setJarat(this);
            jegyek.hozzaad(jegy);
        }
    }
}

void Vonat::jegyekKiir(std::ostream& os) const {
    jegyek.bejar(jegyKiir(os));
}

Jegy* Vonat::jegyKeres(uint ksz, uint hsz) const {
    return jegyek.keres(jegyKeresByPozicio(ksz, hsz));
}

std::istream& operator>>(std::istream& is, Vonat& vonat) {
    uint azonosito;
    string indAllomas, erkAllomas;
    Datum indIdo, erkIdo;
    is >> azonosito >> indAllomas >> indIdo >> erkAllomas >> erkIdo;
    vonat.setAzonosito(azonosito);
    vonat.setIndAllomas(indAllomas);
    vonat.setIndIdo(indIdo);
    vonat.setErkAllomas(erkAllomas);
    vonat.setErkIdo(erkIdo);
    return is;
}

std::ostream& operator<<(std::ostream& os, const Vonat& vonat) {
    os << vonat.getAzonosito() << " " << vonat.getIndAllomas() << " " << vonat.getIndIdo() << " "
       << vonat.getErkAllomas() << " " << vonat.getErkIdo();
    return os;
}

std::istream& operator>>(std::istream& is, HeteroStore<Vonat>& vonatok) {
    Vonat* aktualis = new Vonat();
    while(is >> *aktualis) {
        vonatok.hozzaad(aktualis);
        aktualis = new Vonat();
    }
    delete aktualis;
    return is;
}

std::ostream& operator<<(std::ostream& os, const HeteroStore<Vonat>& vonatok) {
    vonatok.bejar(vonatKiir(os));
    return os;
}
