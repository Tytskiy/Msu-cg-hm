#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include <utility>

#include "Image.h"
#include "Object.h"

class Player : public Object {
   public:
    Player(Point pos = {0, 0}, Size size = {tileSize, tileSize}, Pixel color = {0, 0, 0, 1}, bool is_static = false,
           bool is_colision = true, int speed = 4)
        : Object(pos, size, color, is_static, is_colision), move_speed(speed){};

    bool Moved() const;
    void ProcessInput(MovementDir dir);
    void Draw(Image &screen);
    Size getSize() const;

   private:
    int move_speed;
};

#endif  // MAIN_PLAYER_H
