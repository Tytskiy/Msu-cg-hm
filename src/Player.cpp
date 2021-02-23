#include "Player.h"
#include <iostream>

void Player::move(MovementDir dir, float dt) {
    switch (dir) {
        case MovementDir::UP:
            position.y += dt * velocity;
            break;
        case MovementDir::DOWN:
            position.y -= dt * velocity;
            break;
        case MovementDir::LEFT:
            position.x -= dt * velocity;
            break;
        case MovementDir::RIGHT:
            position.x += dt * velocity;
            break;
        default:
            break;
    }
}