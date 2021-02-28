#ifndef MAIN_PRIMITIVE_H
#define MAIN_PRIMITIVE_H

#include <cstdint>

enum class MovementDir {
    UP, DOWN, LEFT, RIGHT
};
struct Directions {
    bool left = true;
    bool right = true;
    bool top = true;
    bool bottom = true;
};

struct Size {
    int width;
    int height;
};

struct Point {
    int x;
    int y;

    Point operator+(const Point &p) const {
        return Point{x + p.x, y + p.y};
    }

    Point operator-(const Point &p) const {
        return Point{x - p.x, y - p.y};
    }
};

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};
#endif //MAIN_PRIMITIVE_H
