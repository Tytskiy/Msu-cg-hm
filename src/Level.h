#ifndef MAIN_LEVEL_H
#define MAIN_LEVEL_H

#include "primitive.h"

#include "Sprite.h"
#include <string>

class Level {
public:
    Level(const std::string &spritePath, const Size &numTiles, const Point &p);

    Level();

    Sprite *GetMainSprite() const;

    Sprite *GetTileSprite() const;

    Size GetSizeOfLevel() const;

    Point GetStartDraw() const;

private:
    Sprite *mainSprite;
    Sprite *tileSprite;
    Size sizeOfLevel;
    Point startDraw;
};

#endif //MAIN_LEVEL_H
