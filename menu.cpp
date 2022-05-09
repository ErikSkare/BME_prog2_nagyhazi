/**
 * \file menu.cpp
 *
 * A menu.hpp-hez tartozó definíciók.
 */

#include "menu.hpp"
#include "teljesjegy.hpp"
#include "diakjegy.hpp"
#include "gyujtojegy.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::string;

void Menu::megjelenit() {
    while(allapot != KILEPES) {
        switch(allapot) {
            case FOMENU:
                allapot = fomenu_vezerlo();
                break;
            case VONAT_HOZZAADAS:
                allapot = vonat_hozzaadas_vezerlo();
                break;
            case JEGY_KIADAS:
                allapot = jegy_kiadas_vezerlo();
                break;
            case JEGY_ERVENYESITES:
                allapot = jegy_ervenyesites_vezerlo();
                break;
            default:
                allapot = FOMENU;
                break;
        }
        std::cout << "\n-----------------------------------\n\n";
    }
}

MenuAllapot Menu::fomenu_vezerlo() {
    cout << "Fõmenü\n";
    cout << "  1 - Vonat hozzáadása\n";
    cout << "  2 - Jegy kiadása\n";
    cout << "  3 - Jegy érvényesítése\n";
    cout << "  4 - Kilépés\n";
    int utasitas;
    do {
        cout << "Utasítás: ";
        cin >> utasitas;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Utasítás: ";
            cin >> utasitas;
        }
    } while(utasitas < 1 || utasitas > 4);
    return (MenuAllapot) utasitas;
}

MenuAllapot Menu::vonat_hozzaadas_vezerlo() {
    uint azon;
    string indAllomas, erkAllomas;
    Datum indIdo, erkIdo;
    cout << "Vonat hozzáadás\n";
    cout << "  Azonosító: ";
    cin >> azon;
    cout << "  Indulási állomás: ";
    cin >> indAllomas;
    cout << "  Indulási idõ: ";
    cin >> indIdo;
    cout << "  Érkezési állomás: ";
    cin >> erkAllomas;
    cout << "  Érkezési idõ: ";
    cin >> erkIdo;

    Vonat *talalat = vonatok.keres(vonatKeresByAzon(azon));
    if(talalat != NULL) {
        cout << "Ezzel az azonosítóval már van vonat!\n";
        return FOMENU;
    }

    vonatok.hozzaad(new Vonat(azon, indAllomas, indIdo, erkAllomas, erkIdo));
    cout << "Sikerült a hozzáadás!\n";
    return FOMENU;
}

MenuAllapot Menu::jegy_kiadas_vezerlo() {
    uint tipus, vonatAzon, kocsiSzam, helySzam;
    cout << "Jegy kiadás\n";
    cout << "  Jegy típusa: ";
    cin >> tipus;
    cout << "  Vonat azonosítója: ";
    cin >> vonatAzon;
    cout << "  Kocsiszám: ";
    cin >> kocsiSzam;
    cout << "  Helyszám: ";
    cin >> helySzam;

    if(tipus < 1 || tipus > 3) {
        cout << "Nem létezõ típus!\n";
        return FOMENU;
    }

    Vonat *talalat = vonatok.keres(vonatKeresByAzon(vonatAzon));
    if(talalat == NULL) {
        cout << "Nem található a megadott azonosítóval vonat!\n";
        return FOMENU;
    }

    Jegy *ujJegy;
    switch((Jegyek) tipus) {
        case TELJESJEGY: {
            ujJegy = new TeljesJegy(talalat, kocsiSzam, helySzam);
        } break;
        case DIAKJEGY: {
            uint kedvezmeny;
            cout << "  Kedvezmény: ";
            cin >> kedvezmeny;
            ujJegy = new DiakJegy(talalat, kocsiSzam, helySzam, kedvezmeny);
        } break;
        case GYUJTOJEGY: {
            uint darab;
            cout << "  Darab: ";
            cin >> darab;
            ujJegy = new GyujtoJegy(talalat, kocsiSzam, helySzam, darab);
        } break;
    }

    try {
        talalat->jegyHozzaad(ujJegy);
        cout << "Sikerült a hozzáadás!\n";
    } catch(FoglaltHiba& hiba) {
        cout << hiba.what();
    } catch(RosszVonatHiba& hiba) {
        cout << hiba.what();
    }

    return FOMENU;
}

MenuAllapot Menu::jegy_ervenyesites_vezerlo() {
    uint vonatAzon, kocsiSzam, helySzam;
    bool hasSzemelyIg, hasDiakIg;
    cout << "Jegy érvényesítés\n";
    cout << "  Vonat azonosítója: ";
    cin >> vonatAzon;
    cout << "  Kocsiszám: ";
    cin >> kocsiSzam;
    cout << "  Helyszám: ";
    cin >> helySzam;
    cout << "  Van személyigazolvány: ";
    cin >> hasSzemelyIg;
    cout << "  Van diákigazolvány: ";
    cin >> hasDiakIg;

    Vonat *talalat = vonatok.keres(vonatKeresByAzon(vonatAzon));
    if(talalat == NULL) {
        cout << "Nem található a megadott azonosítóval vonat!\n";
        return FOMENU;
    }

    Jegy *ervenyesitendo = talalat->jegyKeres(kocsiSzam, helySzam);
    if(ervenyesitendo == NULL) {
        cout << "Nem található a megadott helyen jegy!\n";
        return FOMENU;
    }

    try {
        Utas ervenyesito(hasSzemelyIg, hasDiakIg);
        ervenyesitendo->ervenyesit(ervenyesito);
        if(!ervenyesitendo->isHasznalhato())
            talalat->jegyTorol(ervenyesitendo);
        cout << "Sikerült az érvényesítés!\n";
    } catch(ErvenyesitesiHiba& hiba) {
        cout << hiba.what();
    }

    return FOMENU;
}
