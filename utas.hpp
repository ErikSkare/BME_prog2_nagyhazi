#ifndef UTAS_HPP
#define UTAS_HPP

/**
 * \file utas.hpp
 *
 * Utas oszt�ly deklar�ci�ja
 */

class Utas {
    bool szemelyIg; ///> Van-e az utasn�l szem�lyigazolv�ny.
    bool diakIg; ///> Van-e az utasn�l di�kigazolv�ny.

public:
    /// Konstruktor
    /// @param szIg - szemelyIg adattag �rt�ke
    /// @param dIg - diakIg adattag �rt�ke
    Utas(bool szIg, bool dIg)
        : szemelyIg(szIg), diakIg(dIg) { }

    /// szemelyIg getter met�dusa
    /// @return szemelyIg
    inline bool hasSzemelyIg() const { return szemelyIg; }

    /// szemelyIg setter met�dusa
    /// @param val - az �j �rt�k
    inline void setSzemelyIg(bool val) { szemelyIg = val; }

    /// diakIg getter met�dusa
    /// @return diakIg
    inline bool hasDiakIg() const { return diakIg; }

    /// diakIg setter met�dusa
    /// @param val - az �j �rt�k
    inline void setDiakIg(bool val) { diakIg = val; }

    /// virtu�lis destruktor
    virtual ~Utas() { }
};

#endif
