#ifndef MAIN_PRIMITIVE_H
#define MAIN_PRIMITIVE_H

#include <cstdint>

enum class MovementDir {
    UP, DOWN, LEFT, RIGHT
};

struct Size {
    int width;
    int height;
};

struct Point {
    int x;
    int y;

};

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
#endif //MAIN_PRIMITIVE_H
