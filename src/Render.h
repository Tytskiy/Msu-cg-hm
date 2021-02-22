#ifndef MAIN_RENDER_H
#define MAIN_RENDER_H

#include <string>

#include "config.h"
#include "primitive.h"
#include "Sprite.h"
#include "GameObject.h"
#include "Level.h"

class Render {
public:
    explicit Render(const std::string &a_path);

    explicit Render(const Sprite &sprite);

    Render(const Pixel &backgroundColor, const Size &size, int a_channels = 4);

    ~Render();

    void DrawStatic();

    void AddLayer(const Sprite &sprite, const Point &leftBottom);

    Sprite *GetDynamicImage() const;

    Sprite *GetSourceImage() const;

    Size GetSizeOfRender() const;

    int GetChannels() const;

    Pixel GetDynamicPixel(const Point &p) const;

    Pixel GetSourcePixel(const Point &p) const;

    bool IsValidPixel(const Point &p) const;

    bool PutPixel(const Point &p, const Pixel &pix);

    bool PutSourcePixel(const Point &p);

    void DrawSquare(const Point &p, const Size &size, const Pixel &color);

    void DrawSprite(const Point &p, const Sprite &sprite);

    void DrawObject(const GameObject &obj);

    void FreeSquare(const Point &p, const Size &size);


private:
    Sprite *dynamicImage;
    Sprite *staticImage;
    Size sizeOfRendering{};
    int channels{};
};

#endif  // MAIN_RENDER_H
