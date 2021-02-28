#ifndef MAIN_RENDER_H
#define MAIN_RENDER_H

#include <string>

#include "config.h"
#include "primitive.h"
#include "Sprite.h"
#include "Level.h"

class Render {
public:
    explicit Render(const std::string &a_path);

    explicit Render(const Sprite &sprite);

    Render(const Pixel &backgroundColor, const Size &size, int a_channels = 4);

    ~Render();

    void drawStatic();

    void addLayer(const Sprite &sprite, const Point &topLeft);

    Sprite *getDynamicImage() const;

    Sprite *getSourceImage() const;

    Size getSizeOfRender() const;

    int getChannels() const;

    Pixel getDynamicPixel(const Point &p) const;

    Pixel getSourcePixel(const Point &p) const;

    bool isValidPixel(const Point &p) const;

    bool putPixel(const Point &p, const Pixel &pix);

    bool putSourcePixel(const Point &p);

    void drawSquare(const Point &p, const Size &size, const Pixel &color);

    void drawSprite(const Sprite &sprite, const Point &p);

    void drawObject(const GameObject &obj);

    void freeSquare(const Point &p, const Size &size);


private:
    Sprite *dynamicImage;
    Sprite *staticImage;
    Size sizeOfRendering{};
    int channels{};
};

#endif  // MAIN_RENDER_H
