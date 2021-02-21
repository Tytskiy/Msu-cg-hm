#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "primitive.h"
#include "Sprite.h"
#include "Render.h"


class GameObject {
public:
    explicit GameObject(Sprite &spr,
                        const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE},
                        bool isStatic = false,
                        bool isColision = true)
            : currCoords(pos), oldCoords(currCoords), size(size),
              isStatic(isStatic), isColision(isColision) {
        sprite = &spr;
    }

    explicit GameObject(const std::string &path,
                        const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE},
                        bool is_static = false,
                        bool is_colision = true) :
            currCoords(pos), oldCoords(currCoords), size(size),
            isStatic(is_static), isColision(is_colision) {
        sprite = new Sprite(path);
    }

    void Draw(Render &screen);

    Size GetSize() const { return size; }

    bool isMoved() const {
        if (currCoords.x == oldCoords.x && currCoords.y == oldCoords.y)
            return false;
        return true;
    }

    ~GameObject() {
        delete sprite;
    }

protected:
    Sprite *sprite = nullptr;
    Size size;
    Point currCoords;
    Point oldCoords;
    bool isStatic;
    bool isColision;
};

#endif