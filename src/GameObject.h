#ifndef MAIN_OBJECT_H
#define MAIN_OBJECT_H

#include "config.h"
#include "primitive.h"
#include "Sprite.h"

class GameObject {
public:
    explicit GameObject(Sprite &spr,
                        const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE}, int vel = 0,
                        bool isStatic = false) :
            position(pos), size(size), isStatic(isStatic), velocity(vel) {
        sprite = &spr;
    }

    explicit GameObject(const std::string &path,
                        const Point &pos = {0, 0},
                        const Size &size = {TILE_SIZE, TILE_SIZE},
                        int vel = 0, bool isStatic = true) :
            position(pos), size(size), isStatic(isStatic), velocity(vel) {
        sprite = new Sprite(path);
    }

    Sprite &getSprite() const {
        return *sprite;
    }

    Size getSize() const {
        return size;
    }

    Point getPosition() const {
        return position;
    }

    void setPosition(const Point &pos) {
        position = pos;
    }

    ~GameObject() {
        delete sprite;
    }

protected:
    Sprite *sprite = nullptr;
    Size size;
    Point position;
    int velocity;
    bool isStatic;
};

#endif