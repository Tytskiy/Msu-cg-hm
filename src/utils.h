#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#include <iostream>

template<typename T>
T *copyFromPointer(const T *p, size_t size)  //перенести в отдельный модуль
{
    T *new_p = new T[size];
    for (size_t i = 0; i < size; i++) {
        new_p[i] = p[i];
    }
    return new_p;
}

template<typename T>
void fillArray(T *p, size_t size, T filler)  //перенести в отдельный модуль
{
    for (size_t i = 0; i < size; i++) {
        p[i] = filler;
    }
}

#endif  // MAIN_UTILS_H