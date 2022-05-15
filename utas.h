#ifndef UTAS_HPP
#define UTAS_HPP

/**
 * \file utas.hpp
 *
 * Utas osztály deklarációja
 */

class Utas {
    bool szemelyIg; ///> Van-e az utasnál személyigazolvány.
    bool diakIg; ///> Van-e az utasnál diákigazolvány.

public:
    /// Konstruktor
    /// @param szIg - szemelyIg adattag értéke
    /// @param dIg - diakIg adattag értéke
    Utas(bool szIg, bool dIg)
        : szemelyIg(szIg), diakIg(dIg) { }

    /// szemelyIg getter metódusa
    /// @return szemelyIg
    inline bool hasSzemelyIg() const { return szemelyIg; }

    /// szemelyIg setter metódusa
    /// @param val - az új érték
    inline void setSzemelyIg(bool val) { szemelyIg = val; }

    /// diakIg getter metódusa
    /// @return diakIg
    inline bool hasDiakIg() const { return diakIg; }

    /// diakIg setter metódusa
    /// @param val - az új érték
    inline void setDiakIg(bool val) { diakIg = val; }

    /// virtuális destruktor
    virtual ~Utas() { }
};

#endif
