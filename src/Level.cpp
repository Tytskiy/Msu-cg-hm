#include "Level.h"

Level::Level(const std::string &levelPath, const Size &numTiles, const int tileSize) :
        sizeOfLevel{tileSize * numTiles.width, tileSize * numTiles.height} {

    std::ifstream tmp(levelPath);
    std::string level((std::istreambuf_iterator<char>(tmp)), std::istreambuf_iterator<char>());
    level.erase(std::remove(level.begin(), level.end(), '\n'), level.end());

    auto tmpPixels = new Pixel[sizeOfLevel.width * sizeOfLevel.height];

    //ЕЩЕ НЕДОДЕЛАЛ
    for (int i = sizeOfLevel.height - 1; i >= 0; i--) {
        for (int j = 0; j < sizeOfLevel.width; j++) {
            char currChar = level[numTiles.width * ((sizeOfLevel.height - 1 - i) / tileSize) + j / tileSize];
            if (currChar == '@') {
                playerPos = {j - TILE_SIZE / 2, i - TILE_SIZE / 2};//последний раз сюда попадаю в правом нижнем углу
            } else if (currChar == '%') {
                //dynamicObjects.push_back(GameObject(levelSprites[currChar],))
            } else {
                auto currSprite = levelSprites[currChar];
                tmpPixels[sizeOfLevel.width * i + j] = currSprite({j % tileSize, i % tileSize});
            }
        }
    }
    staticObjects = new Sprite(tmpPixels, sizeOfLevel);
    delete[] tmpPixels;
}

Level::~Level() {
    delete staticObjects;
}

Sprite &Level::GetStaticObjects() const {
    return *staticObjects;
}

Size Level::GetSize() const {
    return sizeOfLevel;
}