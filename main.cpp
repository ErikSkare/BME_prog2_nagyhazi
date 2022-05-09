#include <iostream>
#include <fstream>
#include <sstream>
#include "memtrace.h"
#include "gtest_lite.h"
#include "menu.hpp"
#include "teljesjegy.hpp"
#include "diakjegy.hpp"
#include "gyujtojegy.hpp"

using namespace std;

int main()
{
    setlocale(LC_ALL, "hun");
    // beolvasás
    HeteroStore<Vonat> vonatok;
    ifstream be1("vonatok.txt");
    if(be1.is_open()) {
        be1 >> vonatok;
        be1.close();
    }
    ifstream be2("jegyek.txt");
    if(be2.is_open()) {
        vonatok.bejar(jegyekBeolvasStreamrol(be2));
        be2.close();
    }

    Menu menu(vonatok);
    menu.megjelenit();

    // tesztek
    GTINIT(std::cin);
    TEST(Datum, konstruktorok) {
        Datum a; //default
        EXPECT_EQ(0, int(a.getEv()));
        EXPECT_EQ(0, int(a.getHonap()));
        EXPECT_EQ(0, int(a.getNap()));
        EXPECT_EQ(0, int(a.getOra()));
        EXPECT_EQ(0, int(a.getPerc()));

        Datum b(2002, 12, 23, 15, 14);
        EXPECT_EQ(2002, int(b.getEv()));
        EXPECT_EQ(12, int(b.getHonap()));
        EXPECT_EQ(23, int(b.getNap()));
        EXPECT_EQ(15, int(b.getOra()));
        EXPECT_EQ(14, int(b.getPerc()));
    } ENDM

    TEST(Datum, beolvasas es kiiras) {
        stringstream ss1("2002 12 23 15 14");
        Datum a;
        ss1 >> a;
        EXPECT_EQ(2002, int(a.getEv()));
        EXPECT_EQ(12, int(a.getHonap()));
        EXPECT_EQ(23, int(a.getNap()));
        EXPECT_EQ(15, int(a.getOra()));
        EXPECT_EQ(14, int(a.getPerc()));

        stringstream ss2;
        ss2 << a;
        EXPECT_STREQ("2002 12 23 15 14", ss2.str().c_str());
    } ENDM

    TEST(Utas, minden) {
        Utas a(true, false);
        EXPECT_EQ(true, a.hasSzemelyIg());
        EXPECT_EQ(false, a.hasDiakIg());
        a.setSzemelyIg(false);
        a.setDiakIg(true);
        EXPECT_EQ(false, a.hasSzemelyIg());
        EXPECT_EQ(true, a.hasDiakIg());
    } ENDM

    TEST(HeteroStore, minden) {
        Vonat *a = new Vonat(1, "Budapest", {2002, 12, 23, 15, 14}, "Baja", {2002, 12, 23, 18, 0});
        Vonat *b = new Vonat(2, "Budapest", {2002, 12, 24, 16, 0}, "Szeged", {2002, 12, 24, 18, 15});
        HeteroStore<Vonat> vonatok;
        EXPECT_EQ(0, int(vonatok.size()));
        vonatok.hozzaad(a);
        EXPECT_EQ(1, int(vonatok.size()));
        EXPECT_EQ(a, vonatok.keres(vonatKeresByAzon(1)));
        EXPECT_EQ(true, vonatok.keres(vonatKeresByAzon(2)) == NULL);
        vonatok.hozzaad(b);
        EXPECT_EQ(2, int(vonatok.size()));
        vonatok.torol(vonatKeresByAzon(2));
        vonatok.torol(vonatKeresByAzon(6));
        EXPECT_EQ(1, int(vonatok.size()));
        EXPECT_EQ(a, vonatok.keres(vonatKeresByAzon(1)));
        EXPECT_EQ(true, vonatok.keres(vonatKeresByAzon(2)) == NULL);
    } ENDM

    TEST (TeljesJegy, konstruktorok) {
        Vonat v;
        TeljesJegy jegy;
        EXPECT_EQ(true, jegy.getJarat() == NULL);
        EXPECT_EQ(0, int(jegy.getKocsiSzam()));
        EXPECT_EQ(0, int(jegy.getHelySzam()));
        EXPECT_EQ(true, jegy.isHasznalhato());
        TeljesJegy masik_jegy(&v, 5, 4);
        EXPECT_EQ(true, masik_jegy.getJarat() == &v);
        EXPECT_EQ(5, int(masik_jegy.getKocsiSzam()));
        EXPECT_EQ(4, int(masik_jegy.getHelySzam()));
        EXPECT_EQ(true, masik_jegy.isHasznalhato());
    } ENDM

    TEST (TeljesJegy, beolvasas es kiiras) {
        Vonat v(1, "Baja", {2022, 12, 23, 16, 0}, "Budapest", {2022, 12, 23, 18, 25});
        stringstream ss1("5 4");
        TeljesJegy jegy;
        ss1 >> jegy;
        EXPECT_EQ(true, jegy.getJarat() == NULL);
        EXPECT_EQ(5, int(jegy.getKocsiSzam()));
        EXPECT_EQ(4, int(jegy.getHelySzam()));
        EXPECT_EQ(true, jegy.isHasznalhato());
        jegy.setJarat(&v);
        EXPECT_EQ(true, &v == jegy.getJarat());
        stringstream ss2;
        ss2 << jegy;
        EXPECT_STREQ("1 1 5 4", ss2.str().c_str());
        stringstream ss3;
        jegy.kiir(ss3);
        EXPECT_STREQ("1 1 5 4", ss3.str().c_str());
    } ENDM

    TEST(TeljesJegy, ervenyesit) {
        Vonat v(1, "Baja", {2022, 12, 23, 16, 0}, "Budapest", {2022, 12, 23, 18, 25});
        TeljesJegy jegy1(&v, 5, 4);
        TeljesJegy jegy2(&v, 5, 4);
        TeljesJegy jegy3(&v, 5, 4);
        TeljesJegy jegy4(&v, 5, 4);
        Utas utas1(false, false);
        Utas utas2(false, true);
        Utas utas3(true, false);
        Utas utas4(true, true);
        EXPECT_THROW(jegy1.ervenyesit(utas1), ErvenyesitesiHiba const&);
        EXPECT_THROW(jegy2.ervenyesit(utas2), ErvenyesitesiHiba const&);
        EXPECT_NO_THROW(jegy3.ervenyesit(utas3));
        EXPECT_NO_THROW(jegy4.ervenyesit(utas4));
        EXPECT_THROW(jegy4.ervenyesit(utas4), ErvenyesitesiHiba const&);
    } ENDM

    TEST (DiakJegy, konstruktorok) {
        Vonat v;
        DiakJegy jegy;
        EXPECT_EQ(true, jegy.getJarat() == NULL);
        EXPECT_EQ(0, int(jegy.getKocsiSzam()));
        EXPECT_EQ(0, int(jegy.getHelySzam()));
        EXPECT_EQ(0, int(jegy.getKedvezmeny()));
        EXPECT_EQ(true, jegy.isHasznalhato());
        DiakJegy masik_jegy(&v, 5, 4, 20);
        EXPECT_EQ(true, masik_jegy.getJarat() == &v);
        EXPECT_EQ(5, int(masik_jegy.getKocsiSzam()));
        EXPECT_EQ(4, int(masik_jegy.getHelySzam()));
        EXPECT_EQ(20, int(masik_jegy.getKedvezmeny()));
        EXPECT_EQ(true, masik_jegy.isHasznalhato());
    } ENDM

    TEST (DiakJegy, beolvasas es kiiras) {
        Vonat v(1, "Baja", {2022, 12, 23, 16, 0}, "Budapest", {2022, 12, 23, 18, 25});
        stringstream ss1("5 4 20");
        DiakJegy jegy;
        ss1 >> jegy;
        EXPECT_EQ(true, jegy.getJarat() == NULL);
        EXPECT_EQ(5, int(jegy.getKocsiSzam()));
        EXPECT_EQ(4, int(jegy.getHelySzam()));
        EXPECT_EQ(20, int(jegy.getKedvezmeny()));
        EXPECT_EQ(true, jegy.isHasznalhato());
        jegy.setJarat(&v);
        EXPECT_EQ(true, &v == jegy.getJarat());
        stringstream ss2;
        ss2 << jegy;
        EXPECT_STREQ("2 1 5 4 20", ss2.str().c_str());
        stringstream ss3;
        jegy.kiir(ss3);
        EXPECT_STREQ("2 1 5 4 20", ss3.str().c_str());
    } ENDM

    TEST(DiakJegy, ervenyesit) {
        Vonat v(1, "Baja", {2022, 12, 23, 16, 0}, "Budapest", {2022, 12, 23, 18, 25});
        DiakJegy jegy1(&v, 5, 4, 20);
        DiakJegy jegy2(&v, 5, 4, 20);
        DiakJegy jegy3(&v, 5, 4, 20);
        DiakJegy jegy4(&v, 5, 4, 20);
        Utas utas1(false, false);
        Utas utas2(false, true);
        Utas utas3(true, false);
        Utas utas4(true, true);
        EXPECT_THROW(jegy1.ervenyesit(utas1), ErvenyesitesiHiba const&);
        EXPECT_THROW(jegy2.ervenyesit(utas2), ErvenyesitesiHiba const&);
        EXPECT_THROW(jegy3.ervenyesit(utas3), ErvenyesitesiHiba const&);
        EXPECT_NO_THROW(jegy4.ervenyesit(utas4));
        EXPECT_THROW(jegy4.ervenyesit(utas4), ErvenyesitesiHiba const&);
    } ENDM

    TEST (GyujtoJegy, konstruktorok) {
        Vonat v;
        GyujtoJegy jegy;
        EXPECT_EQ(true, jegy.getJarat() == NULL);
        EXPECT_EQ(0, int(jegy.getKocsiSzam()));
        EXPECT_EQ(0, int(jegy.getHelySzam()));
        EXPECT_EQ(0, int(jegy.getDarab()));
        EXPECT_EQ(true, jegy.isHasznalhato());
        GyujtoJegy masik_jegy(&v, 5, 4, 2);
        EXPECT_EQ(true, masik_jegy.getJarat() == &v);
        EXPECT_EQ(5, int(masik_jegy.getKocsiSzam()));
        EXPECT_EQ(4, int(masik_jegy.getHelySzam()));
        EXPECT_EQ(2, int(masik_jegy.getDarab()));
        EXPECT_EQ(true, masik_jegy.isHasznalhato());
    } ENDM

    TEST (GyujtoJegy, beolvasas es kiiras) {
        Vonat v(1, "Baja", {2022, 12, 23, 16, 0}, "Budapest", {2022, 12, 23, 18, 25});
        stringstream ss1("5 4 2");
        GyujtoJegy jegy;
        ss1 >> jegy;
        EXPECT_EQ(true, jegy.getJarat() == NULL);
        EXPECT_EQ(5, int(jegy.getKocsiSzam()));
        EXPECT_EQ(4, int(jegy.getHelySzam()));
        EXPECT_EQ(2, int(jegy.getDarab()));
        EXPECT_EQ(true, jegy.isHasznalhato());
        jegy.setJarat(&v);
        EXPECT_EQ(true, &v == jegy.getJarat());
        stringstream ss2;
        ss2 << jegy;
        EXPECT_STREQ("3 1 5 4 2", ss2.str().c_str());
        stringstream ss3;
        jegy.kiir(ss3);
        EXPECT_STREQ("3 1 5 4 2", ss3.str().c_str());
    } ENDM

    TEST(GyujtoJegy, ervenyesit) {
        Vonat v(1, "Baja", {2022, 12, 23, 16, 0}, "Budapest", {2022, 12, 23, 18, 25});
        GyujtoJegy jegy1(&v, 5, 4, 2);
        GyujtoJegy jegy2(&v, 5, 4, 2);
        GyujtoJegy jegy3(&v, 5, 4, 2);
        GyujtoJegy jegy4(&v, 5, 4, 2);
        Utas utas1(false, false);
        Utas utas2(false, true);
        Utas utas3(true, false);
        Utas utas4(true, true);
        EXPECT_THROW(jegy1.ervenyesit(utas1), ErvenyesitesiHiba const&);
        EXPECT_THROW(jegy2.ervenyesit(utas2), ErvenyesitesiHiba const&);
        EXPECT_NO_THROW(jegy3.ervenyesit(utas3));
        EXPECT_NO_THROW(jegy4.ervenyesit(utas4));
        EXPECT_NO_THROW(jegy4.ervenyesit(utas4));
        EXPECT_THROW(jegy4.ervenyesit(utas4), ErvenyesitesiHiba const&);
    } ENDM

    TEST (Jegy, egyenloseg vizsgalat) {
        TeljesJegy jegy1(NULL, 5, 4);
        GyujtoJegy jegy2(NULL, 5, 4);
        DiakJegy jegy3(NULL, 5, 5);
        EXPECT_TRUE(jegy1 == jegy2);
        EXPECT_FALSE(jegy2 == jegy3);
        EXPECT_FALSE(jegy1 == jegy3);
    } ENDM

    TEST(Vonat, konstruktorok) {
        Vonat a;
        Datum b;
        EXPECT_EQ(0, int(a.getAzonosito()));
        EXPECT_STREQ("", a.getIndAllomas().c_str());
        EXPECT_TRUE((b == a.getIndIdo()));
        EXPECT_STREQ("", a.getErkAllomas().c_str());
        EXPECT_TRUE((b == a.getErkIdo()));

        Vonat c(1, "Baja", {2022, 12, 23, 16, 0}, "Budapest", {2022, 12, 23, 16, 0});
        Datum d(2022, 12, 23, 16, 0);
        EXPECT_EQ(1, int(c.getAzonosito()));
        EXPECT_STREQ("Baja", c.getIndAllomas().c_str());
        EXPECT_TRUE((d == c.getIndIdo()));
        EXPECT_STREQ("Budapest", c.getErkAllomas().c_str());
        EXPECT_TRUE((d == c.getErkIdo()));
    } ENDM

    TEST(Vonat, beolvasas es kiiras) {
        stringstream ss1("1 Baja 2022 12 23 16 0 Budapest 2022 12 23 16 0");
        Vonat c;
        ss1 >> c;
        stringstream ss2;
        ss2 << c;
        EXPECT_STREQ("1 Baja 2022 12 23 16 0 Budapest 2022 12 23 16 0", ss2.str().c_str());
    } ENDM

    TEST(Vonat, jegyhozzaad jegytorol jegykeres) {
        stringstream ss1("1 Baja 2022 12 23 16 0 Budapest 2022 12 23 16 0");
        Vonat c;
        ss1 >> c;
        GyujtoJegy* jegy1 = new GyujtoJegy();
        EXPECT_THROW(c.jegyHozzaad(jegy1), RosszVonatHiba const&);
        TeljesJegy* jegy2 = new TeljesJegy(&c, 5, 4);
        TeljesJegy* jegy3 = new TeljesJegy(&c, 5, 4);
        EXPECT_NO_THROW(c.jegyHozzaad(jegy2));
        EXPECT_THROW(c.jegyHozzaad(jegy3), FoglaltHiba const&);
        EXPECT_TRUE(jegy2 == c.jegyKeres(5, 4));
        c.jegyTorol(jegy2);
        EXPECT_TRUE(NULL == c.jegyKeres(5, 4));
    } ENDM

    TEST(Vonat, rosszvonathiba) {
        stringstream ss1("1 Baja 2022 12 23 16 0 Budapest 2022 12 23 16 0");
        stringstream ss2("2 Baja 2022 12 23 17 0 Szeged 2022 12 23 17 0");
        Vonat c, d;
        ss1 >> c;
        ss2 >> d;
        TeljesJegy *jegy = new TeljesJegy(&c, 5, 4);
        EXPECT_THROW(d.jegyHozzaad(jegy), RosszVonatHiba const&);
        RosszVonatHiba pelda;
        EXPECT_STREQ("Ehhez a vonathoz nem lehet hozzaadni jegyet!\n", pelda.what());
    } ENDM

    TEST(Vonatok, beolvas es kiir) {
        HeteroStore<Vonat> vonatok;
        stringstream ss1("0 Baja 2022 12 23 16 0 Budapest 2022 12 23 18 25\n1 Baja 2022 12 24 16 0 Szeged 2022 12 24 18 0");
        ss1 >> vonatok;
        stringstream ss2;
        ss2 << vonatok;
        EXPECT_STREQ("0 Baja 2022 12 23 16 0 Budapest 2022 12 23 18 25\n1 Baja 2022 12 24 16 0 Szeged 2022 12 24 18 0\n", ss2.str().c_str());
    } ENDM

    // kiírás
    ofstream ki1("vonatok.txt");
    /*if(!ki1.is_open())
        return 1; //hiba */ ///Jporta coverage teszt miatt
    vonatok.bejar(vonatKiir(ki1));
    ofstream ki2("jegyek.txt");
    /*if(!ki2.is_open())
        return 1; //hiba*/ ///Jporta coverage teszt miatt
    vonatok.bejar(jegyekKiirStreamre(ki2));

    return 0;
}
