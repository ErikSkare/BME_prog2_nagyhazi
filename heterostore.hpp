#ifndef HETEROSTORE_HPP
#define HETEROSTORE_HPP

/**
 * \file heterostore.hpp
 *
 * HeteroStore osztály deklarációja
 */

#include <iostream>

template <typename T>
class HeteroStore {
    T** a; ///> adatokra mutató pointerek tömbje.
    size_t N; ///> a kollekció aktuális mérete.

public:
    /// Konstruktor
    /// Egy 0 méretû kollekció inicializálódik.
    HeteroStore() : a(NULL), N(0) { }

    /// megadja a kollekció aktuális méretét
    /// @return N
    inline size_t size() const { return N; }

    /// Hozzáad egy új elemet a tárolóhoz
    /// @param ptr - az új elemre mutató pointer
    /// a tároló felelőssége a felszabadítás!
    void hozzaad(T* ptr);

    /// Az első olyan elemet törli, amelyre a predikátum teljesül. (vagy semmit)
    /// @param unpred - a predikátum
    template <typename Pred>
    void torol(Pred unpred);

    /// Az első olyan elemet adja vissza, amelyre a predikátum teljesül.
    /// @param unpred - a predikátum
    /// @return a megtalált elemre mutató pointer, vagy NULL, ha nem talált semmit.
    template <typename Pred>
    T* keres(Pred unpred) const;

    /// Az összes elemre meghívja a predikátumot.
    /// @param unpred - a predikátum
    template <typename Pred>
    void bejar(Pred unpred) const;

    /// virtuális destruktor
    virtual ~HeteroStore();
};

#endif
