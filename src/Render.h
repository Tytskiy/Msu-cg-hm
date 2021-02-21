#ifndef MAIN_RENDER_H
#define MAIN_RENDER_H

#include "primitive.h"
#include "Level.h"
#include "Sprite.h"
#include <string>

constexpr int TILE_SIZE = 24;  //кратно 2

class Render {
public:
    explicit Render(const std::string &a_path);

    explicit Render(const Level &level);

    explicit Render(const Sprite &image);

    Render(const Pixel &backgroundColor, const Size &size, int a_channels);

    Size GetSizeOfRender() const;

    int GetChannels() const;

    Sprite *DynamicImage() const;

    Sprite *SourceImage() const;

    bool IsValidPixel(const Point &p) const;

    Pixel GetDynamicPixel(const Point &p) const;

    Pixel GetSourcePixel(const Point &p) const;

    bool PutPixel(const Point &p, const Pixel &pix);

    bool PutSourcePixel(const Point &p);

    void DrawSquare(const Point &p, const Size &size, const Pixel &color);

    void DrawSpriteSquare(const Point &p, const Sprite &sprite);

    void FreeSquare(const Point &p, const Size &size);

    ~Render();

private:
    Sprite *dynamicImage;
    Sprite *sourceImage;
    Size sizeOfRendering{};
    int channels{};
};

#endif  // MAIN_RENDER_H
