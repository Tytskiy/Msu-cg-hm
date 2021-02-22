#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

#include "config.h"
#include "primitive.h"
#include "Sprite.h"
#include "GameObject.h"

/*
Базовый набор:
пустое пространство: ‘ ‘ (пробел)
стена: ‘#’
пол: ‘.’
игрок: ‘@’
выход с уровня: ‘x’
стены, которые игрок может разрушить: ‘%’6
 */

static std::map<char, Sprite> levelSprites = {
        {' ', Sprite("../resources/lava.png")},
        {'#', Sprite("../resources/wall.png")},
        {'.', Sprite("../resources/floor.png")},
        {'x', Sprite("../resources/finish.png")},
        {'%', Sprite("../resources/destruct_wall.png")},
        {'@', Sprite()}
};

class Level {
public:
    Level(const std::string &levelPath, const Size &numTiles, const int tileSize = 24);

    ~Level();

    Sprite &GetStaticObjects() const;

    Size GetSize() const;


private:
    Sprite *staticObjects;
    Size sizeOfLevel;
    Point playerPos;
    std::vector<GameObject> dynamicObjects;
};

#endif //MAIN_LEVEL_H
