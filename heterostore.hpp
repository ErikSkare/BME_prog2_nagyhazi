#ifndef HETEROSTORE_HPP
#define HETEROSTORE_HPP

/**
 * \file heterostore.hpp
 *
 * HeteroStore osztály deklarációja
 */

#include <stdexcept>

template <typename T, class E = std::out_of_range>
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

    // TODO: folytatni!

    /// virtuális destruktor
    virtual ~HeteroStore() { }
};

#endif
