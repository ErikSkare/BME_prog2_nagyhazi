#ifndef MENU_HPP
#define MENU_HPP

/**
 * \file menu.hpp
 *
 * Menürendszer megvalósítása!
 */

#include "vonat.hpp"

enum MenuAllapot {
    FOMENU = 0,
    VONAT_HOZZAADAS = 1,
    JEGY_KIADAS = 2,
    JEGY_ERVENYESITES = 3,
    KILEPES = 4
};

class Menu {
    MenuAllapot allapot;
    HeteroStore<Vonat>& vonatok;

public:
    Menu(HeteroStore<Vonat>& vonatok)
        : allapot(FOMENU), vonatok(vonatok) { }

    void megjelenit();

    virtual ~Menu() { }

private:
    MenuAllapot fomenu_vezerlo();
    MenuAllapot vonat_hozzaadas_vezerlo();
    MenuAllapot jegy_kiadas_vezerlo();
    MenuAllapot jegy_ervenyesites_vezerlo();
};

#endif
