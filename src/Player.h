#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include <utility>

#include "Render.h"
#include "Sprite.h"
#include "GameObject.h"

class Player : public GameObject {
public:
    explicit Player(Sprite &spr, const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE},
                    bool isStatic = false,
                    bool isColision = true, int velocity = 200)
            : GameObject(spr, pos, size, isStatic, isColision), velocity(velocity) {};

    explicit Player(const std::string &path, const Point &pos = {0, 0}, const Size &size = {TILE_SIZE, TILE_SIZE},
                    bool is_static = false,
                    bool is_colision = true, int velocity = 200)
            : GameObject(path, pos, size, is_static, is_colision), velocity(velocity) {};

    void Move(MovementDir dir, float dt);

    void Draw(Render &screen);

private:
    int velocity;
};

#endif  // MAIN_PLAYER_H
