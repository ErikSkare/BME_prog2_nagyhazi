/**
 * \file menu.cpp
 *
 * A menu.hpp-hez tartoz� defin�ci�k.
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
    cout << "F�men�\n";
    cout << "  1 - Vonat hozz�ad�sa\n";
    cout << "  2 - Jegy kiad�sa\n";
    cout << "  3 - Jegy �rv�nyes�t�se\n";
    cout << "  4 - Kil�p�s\n";
    int utasitas;
    do {
        cout << "Utas�t�s: ";
        cin >> utasitas;
        while(cin.fail()) {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Utas�t�s: ";
            cin >> utasitas;
        }
    } while(utasitas < 1 || utasitas > 4);
    return (MenuAllapot) utasitas;
}

MenuAllapot Menu::vonat_hozzaadas_vezerlo() {
    uint azon;
    string indAllomas, erkAllomas;
    Datum indIdo, erkIdo;
    cout << "Vonat hozz�ad�s\n";
    cout << "  Azonos�t�: ";
    cin >> azon;
    cout << "  Indul�si �llom�s: ";
    cin >> indAllomas;
    cout << "  Indul�si id�: ";
    cin >> indIdo;
    cout << "  �rkez�si �llom�s: ";
    cin >> erkAllomas;
    cout << "  �rkez�si id�: ";
    cin >> erkIdo;

    Vonat *talalat = vonatok.keres(vonatKeresByAzon(azon));
    if(talalat != NULL) {
        cout << "Ezzel az azonos�t�val m�r van vonat!\n";
        return FOMENU;
    }

    vonatok.hozzaad(new Vonat(azon, indAllomas, indIdo, erkAllomas, erkIdo));
    cout << "Siker�lt a hozz�ad�s!\n";
    return FOMENU;
}

MenuAllapot Menu::jegy_kiadas_vezerlo() {
    uint tipus, vonatAzon, kocsiSzam, helySzam;
    cout << "Jegy kiad�s\n";
    cout << "  Jegy t�pusa: ";
    cin >> tipus;
    cout << "  Vonat azonos�t�ja: ";
    cin >> vonatAzon;
    cout << "  Kocsisz�m: ";
    cin >> kocsiSzam;
    cout << "  Helysz�m: ";
    cin >> helySzam;

    if(tipus < 1 || tipus > 3) {
        cout << "Nem l�tez� t�pus!\n";
        return FOMENU;
    }

    Vonat *talalat = vonatok.keres(vonatKeresByAzon(vonatAzon));
    if(talalat == NULL) {
        cout << "Nem tal�lhat� a megadott azonos�t�val vonat!\n";
        return FOMENU;
    }

    Jegy *ujJegy;
    switch((Jegyek) tipus) {
        case TELJESJEGY: {
            ujJegy = new TeljesJegy(talalat, kocsiSzam, helySzam);
        } break;
        case DIAKJEGY: {
            uint kedvezmeny;
            cout << "  Kedvezm�ny: ";
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
        cout << "Siker�lt a hozz�ad�s!\n";
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
    cout << "Jegy �rv�nyes�t�s\n";
    cout << "  Vonat azonos�t�ja: ";
    cin >> vonatAzon;
    cout << "  Kocsisz�m: ";
    cin >> kocsiSzam;
    cout << "  Helysz�m: ";
    cin >> helySzam;
    cout << "  Van szem�lyigazolv�ny: ";
    cin >> hasSzemelyIg;
    cout << "  Van di�kigazolv�ny: ";
    cin >> hasDiakIg;

    Vonat *talalat = vonatok.keres(vonatKeresByAzon(vonatAzon));
    if(talalat == NULL) {
        cout << "Nem tal�lhat� a megadott azonos�t�val vonat!\n";
        return FOMENU;
    }

    Jegy *ervenyesitendo = talalat->jegyKeres(kocsiSzam, helySzam);
    if(ervenyesitendo == NULL) {
        cout << "Nem tal�lhat� a megadott helyen jegy!\n";
        return FOMENU;
    }

    try {
        Utas ervenyesito(hasSzemelyIg, hasDiakIg);
        ervenyesitendo->ervenyesit(ervenyesito);
        if(!ervenyesitendo->isHasznalhato())
            talalat->jegyTorol(ervenyesitendo);
        cout << "Siker�lt az �rv�nyes�t�s!\n";
    } catch(ErvenyesitesiHiba& hiba) {
        cout << hiba.what();
    }

    return FOMENU;
}
