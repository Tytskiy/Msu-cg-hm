#include "Player.h"
#include <iostream>

void Player::Move(MovementDir dir, float dt) {
    switch (dir) {
        case MovementDir::UP:
            oldCoords.y = currCoords.y;
            currCoords.y += dt * velocity;
            break;
        case MovementDir::DOWN:
            oldCoords.y = currCoords.y;
            currCoords.y -= dt * velocity;
            break;
        case MovementDir::LEFT:
            oldCoords.x = currCoords.x;
            currCoords.x -= dt * velocity;
            break;
        case MovementDir::RIGHT:
            oldCoords.x = currCoords.x;
            currCoords.x += dt * velocity;
            break;
        default:
            break;
    }
}

void Player::Draw(Render &screen) {
    if (isMoved()) {
        screen.FreeSquare(oldCoords, sprite->GetSize());
        oldCoords = currCoords;
    }
    if (sprite) {
        screen.DrawSpriteSquare(currCoords, *sprite);
    } else {
        screen.DrawSquare(currCoords, size, {255, 255, 255, 255});
    }
}
