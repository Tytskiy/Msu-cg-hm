#ifndef MAIN_UTILS_H
#define MAIN_UTILS_H

#include <iostream>

template<typename T>
T *copyFromPointer(const T *p, size_t size) {
    T *new_p = new T[size];
    for (size_t i = 0; i < size; i++) {
        new_p[i] = p[i];
    }
    return new_p;
}

template<typename T>
void fillArray(T *p, size_t size, T filler) {
    for (size_t i = 0; i < size; i++) {
        p[i] = filler;
    }
}

template<typename T>
void fillMatrix(T *p, size_t width, T *filler, size_t f_width, size_t f_height, int x, int y) {
    for (size_t i = 0; i < f_height; i++) {
        for (size_t j = 0; j < f_width; j++) {
            p[width * (i + y) + j + x] = filler[f_width * i + j];
        }
    }
}

template<typename T>
void fillMatrix(T *p, size_t width, T fill, size_t f_width, size_t f_height, int x, int y) {
    for (size_t i = 0; i < f_height; i++) {
        for (size_t j = 0; j < f_width; j++) {
            p[width * (i + y) + j + x] = fill;
        }
    }
}

#endif  // MAIN_UTILS_H