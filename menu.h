#ifndef MENU_H
#define MENU_H

/**
 * \file menu.h
 *
 * Menürendszer megvalósítása!
 */

#include "vonat.h"

/// A menü állapota
enum MenuAllapot {
    FOMENU = 0,
    VONAT_HOZZAADAS = 1,
    JEGY_KIADAS = 2,
    JEGY_ERVENYESITES = 3,
    KILEPES = 4
};

class Menu {
    MenuAllapot allapot; ///> A menü aktuális állapota
    HeteroStore<Vonat>& vonatok; ///> A vonatok heterogén kollekció, amin a mûveleteket végezzük

public:
    /// Konstruktor
    Menu(HeteroStore<Vonat>& vonatok)
        : allapot(FOMENU), vonatok(vonatok) { }

    /// Megjeleníti a menüt, akkor lép ki, ha KILEPES allapotba került.
    void megjelenit();

    /// virtuális destruktor
    virtual ~Menu() { }

private:
    /// Vezérlõ függvények, visszaadják a következõ állapotot
    MenuAllapot fomenu_vezerlo();
    MenuAllapot vonat_hozzaadas_vezerlo();
    MenuAllapot jegy_kiadas_vezerlo();
    MenuAllapot jegy_ervenyesites_vezerlo();
};

#endif
