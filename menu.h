#ifndef MENU_H
#define MENU_H

/**
 * \file menu.h
 *
 * Men�rendszer megval�s�t�sa!
 */

#include "vonat.h"

/// A men� �llapota
enum MenuAllapot {
    FOMENU = 0,
    VONAT_HOZZAADAS = 1,
    JEGY_KIADAS = 2,
    JEGY_ERVENYESITES = 3,
    KILEPES = 4
};

class Menu {
    MenuAllapot allapot; ///> A men� aktu�lis �llapota
    HeteroStore<Vonat>& vonatok; ///> A vonatok heterog�n kollekci�, amin a m�veleteket v�gezz�k

public:
    /// Konstruktor
    Menu(HeteroStore<Vonat>& vonatok)
        : allapot(FOMENU), vonatok(vonatok) { }

    /// Megjelen�ti a men�t, akkor l�p ki, ha KILEPES allapotba ker�lt.
    void megjelenit();

    /// virtu�lis destruktor
    virtual ~Menu() { }

private:
    /// Vez�rl� f�ggv�nyek, visszaadj�k a k�vetkez� �llapotot
    MenuAllapot fomenu_vezerlo();
    MenuAllapot vonat_hozzaadas_vezerlo();
    MenuAllapot jegy_kiadas_vezerlo();
    MenuAllapot jegy_ervenyesites_vezerlo();
};

#endif
