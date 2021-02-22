#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include <utility>

#include "Render.h"
#include "Sprite.h"
#include "GameObject.h"

class Player : public GameObject {
public:
    explicit Player(Sprite &spr, const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE},
                    bool isStatic = false, int vel = 200)
            : GameObject(spr, pos, size, vel, isStatic) {
    };

    explicit Player(const std::string &path, const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE},
                    bool is_static = false, int vel = 200)
            : GameObject(path, pos, size, vel, is_static) {
    };

    void Move(MovementDir dir, float dt);
};

#endif  // MAIN_PLAYER_H
