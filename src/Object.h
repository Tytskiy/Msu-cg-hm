#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "Image.h"

struct Size {
    int width;
    int height;
};

struct Point {
    int x;
    int y;
};

enum class MovementDir { UP, DOWN, LEFT, RIGHT };

class Object {
   public:
    Object(Point pos = {0, 0}, Size size = {tileSize, tileSize}, Pixel color = {0, 0, 0, 1}, bool is_static = true,
           bool is_colision = true)
        : coords(pos), old_coords(coords), size(size), color(color), is_static(is_static), is_colision(is_colision){};
    virtual void Draw(Image &screen) = 0;
    virtual Size getSize() const = 0;
    virtual bool Moved() const = 0;
    virtual ~Object(){};

   protected:
    Size size;
    Point coords;
    Point old_coords;
    Pixel color;
    bool is_static;
    bool is_colision;
};

#endif