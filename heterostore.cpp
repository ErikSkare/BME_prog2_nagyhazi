#ifndef HETEROSTORE_CPP
#define HETEROSTORE_CPP

/**
 * \file heterostore.cpp
 *
 * A heterostore.hpp-hez tartozó definíciók.
 */

#include "heterostore.hpp"

template <typename T>
void HeteroStore<T>::hozzaad(T* ptr) {
    T** uj_a = new T*[N + 1];
    for(size_t i = 0; i < N; ++i)
        uj_a[i] = a[i];
    uj_a[N++] = ptr;
    delete[] a;
    a = uj_a;
}

template <typename T>
template <typename Pred>
void HeteroStore<T>::torol(Pred unpred) {
    size_t id = 0;
    while(id < N && !unpred(a[id])) ++id;
    if(id == N)
        return;
    T** uj_a = new T*[N - 1];
    for(size_t i = 0; i < id; ++i)
        uj_a[i] = a[i];
    for(size_t i = id + 1; i < N; ++i)
        uj_a[i-1] = a[i];
    delete a[id];
    delete[] a;
    a = uj_a;
    --N;
}

template <typename T>
template <typename Pred>
T* HeteroStore<T>::keres(Pred unpred) const {
    size_t id = 0;
    while(id < N && !unpred(a[id])) ++id;
    if(id == N)
        return NULL;
    else
        return a[id];
}

template <typename T>
template <typename Pred>
void HeteroStore<T>::bejar(Pred unpred) const {
    for(size_t i = 0; i < N; ++i)
        unpred(a[i]);
}

template <typename T>
HeteroStore<T>::~HeteroStore() {
    for(size_t i = 0; i < N; ++i)
        delete a[i];
    delete[] a;
}

#endif
