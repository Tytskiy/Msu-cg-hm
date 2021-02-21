#include <iostream>
#include "Level.h"

Level::Level() = default;

Level::Level(const std::string &spritePath, const Size &numTiles, const Point &p) : startDraw(p) {

    tileSprite = new Sprite(spritePath);
    auto tileS = tileSprite->GetSize();
    sizeOfLevel = {tileS.width * numTiles.width, tileS.height * numTiles.height};
    std::cout << sizeOfLevel.width << " " << sizeOfLevel.height << std::endl;
    auto tmp_pixels = new Pixel[sizeOfLevel.width * sizeOfLevel.height];
    for (int i = 0; i < sizeOfLevel.width; i++) {
        for (int j = 0; j < sizeOfLevel.height; j++) {
            auto tmp = tileSprite->GetImage()[tileS.width * (j % tileS.height) + i % tileS.width];
            tmp_pixels[sizeOfLevel.width * j + i] = tmp;
        }
    }
    mainSprite = new Sprite(tmp_pixels, sizeOfLevel);
    delete[] tmp_pixels;
}


Sprite *Level::GetMainSprite() const {
    return mainSprite;
}

Sprite *Level::GetTileSprite() const {
    return tileSprite;
}

Size Level::GetSizeOfLevel() const {
    return sizeOfLevel;
}

Point Level::GetStartDraw() const {
    return startDraw;
}
