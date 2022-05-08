#ifndef HETEROSTORE_HPP
#define HETEROSTORE_HPP

/**
 * \file heterostore.hpp
 *
 * HeteroStore oszt�ly deklar�ci�ja
 */

#include <stdexcept>

template <typename T, class E = std::out_of_range>
class HeteroStore {
    T** a; ///> adatokra mutat� pointerek t�mbje.
    size_t N; ///> a kollekci� aktu�lis m�rete.

public:
    /// Konstruktor
    /// Egy 0 m�ret� kollekci� inicializ�l�dik.
    HeteroStore() : a(NULL), N(0) { }

    /// megadja a kollekci� aktu�lis m�ret�t
    /// @return N
    inline size_t size() const { return N; }

    // TODO: folytatni!

    /// virtu�lis destruktor
    virtual ~HeteroStore() { }
};

#endif
