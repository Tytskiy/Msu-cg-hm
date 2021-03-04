#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <algorithm>
#include <map>

#include "config.h"
#include "primitive.h"
#include "Sprite.h"
#include "GameObject.h"

static std::map<char, Sprite> levelSprites = {
        {' ', Sprite("../resources/lava.png")},
        {'#', Sprite("../resources/wall.png")},
        {'.', Sprite("../resources/floor.png")},
        {'x', Sprite("../resources/finish.png")},
        {'%', Sprite("../resources/destruct_wall.png")},
        {'D', Sprite("../resources/door_1.png")},
        {'@', Sprite("../resources/doomguy.png")}
};

class Level {
public:
    Level(const std::string &levelPath, const Size &numTiles);

    ~Level();

    bool *getCollisionMap() const;

    Sprite &getStaticObjects() const;

    std::list<GameObject *> &getDO();

    Size getSize() const;

    void setTile(const Sprite &sprite, const Point &topLeft);

    void setCollision(const Point &topLeft);

    const Point &getPlayerPosition() const;

    const Point &getLevelPosition() const;

    void setLevelPosition(const Point &p);

private:
    Sprite *staticObjects;
    std::list<GameObject *> dynamicObjects;
    bool *collisionMap;
    Size sizeOfLevel;
    Point levelPos;
    Point playerPos;
};

#endif //MAIN_LEVEL_H
