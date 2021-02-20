#include "Player.h"

bool Player::Moved() const {
    if (coords.x == old_coords.x && coords.y == old_coords.y)
        return false;
    else
        return true;
}

void Player::ProcessInput(MovementDir dir) {
    int move_dist = move_speed * 1;
    switch (dir) {
        case MovementDir::UP:
            old_coords.y = coords.y;
            coords.y += move_dist;
            break;
        case MovementDir::DOWN:
            old_coords.y = coords.y;
            coords.y -= move_dist;
            break;
        case MovementDir::LEFT:
            old_coords.x = coords.x;
            coords.x -= move_dist;
            break;
        case MovementDir::RIGHT:
            old_coords.x = coords.x;
            coords.x += move_dist;
            break;
        default:
            break;
    }
}

void Player::Draw(Image &screen) {
    if (Moved()) {
        screen.FreeSquare(old_coords.x, old_coords.y, size.width, size.height);
        old_coords = coords;
    }
    screen.DrawSquare(coords.x, coords.y, size.width, size.height, color);
}
Size Player::getSize() const { return size; }