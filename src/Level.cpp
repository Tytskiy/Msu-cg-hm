#include "Level.h"

Level::Level(const std::string &levelPath, const Size &numTiles) :
        sizeOfLevel{TILE_SIZE * numTiles.width, TILE_SIZE * numTiles.height} {

    std::ifstream tmp(levelPath);
    std::string textLevel((std::istreambuf_iterator<char>(tmp)), std::istreambuf_iterator<char>());
    textLevel.erase(std::remove(textLevel.begin(), textLevel.end(), '\n'), textLevel.end());

    staticObjects = new Sprite({255, 255, 255, 255}, {sizeOfLevel.width, sizeOfLevel.height});
    colisionMap = new bool[sizeOfLevel.width * sizeOfLevel.height];

    for (int k = 0; k < textLevel.size(); k++) {
        auto currSprite = levelSprites[textLevel[k]];
        auto currPosition = Point{TILE_SIZE * (k % numTiles.width), TILE_SIZE * (k / numTiles.width)};
        if (textLevel[k] == '@') {
            playerPos = currPosition;
        } else if (textLevel[k] == '%') {
            //dynamicObjects.emplace_back(GameObject(currSprite));
        } else {
            setTile(currSprite, currPosition);
        }
    }

}

Level::~Level() {
    delete staticObjects;
    delete colisionMap;
}

void Level::setTile(const Sprite &sprite, const Point &topLeft) {
    for (int i = 0; i < TILE_SIZE; i++) {
        for (int j = 0; j < TILE_SIZE; j++) {
            staticObjects->setPixel({topLeft.x + j, topLeft.y + i}, sprite({j, i}));
        }
    }
}

const Point Level::getPlayerPosition() const {
    return playerPos;
}


Sprite &Level::getStaticObjects() const {
    return *staticObjects;
}

Size Level::getSize() const {
    return sizeOfLevel;
}
