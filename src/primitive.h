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

    Pixel operator+(const Pixel &p) const {
        return Pixel{(uint8_t) (r + p.r), (uint8_t) (g + p.g), (uint8_t) (b + p.b), (uint8_t) (a + p.a)};
    }

    Pixel operator*(float alpha) const {
        return Pixel{(uint8_t) (alpha * r), (uint8_t) (alpha * g), (uint8_t) (alpha * b), a};
    }

};

#endif //MAIN_PRIMITIVE_H
