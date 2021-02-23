#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include <string>

#include "primitive.h"

struct Sprite {
    Sprite();

    explicit Sprite(Pixel color, Size size, int channels = 4);

    explicit Sprite(const Pixel *pixels, Size size, int channel = 4);

    explicit Sprite(const std::string &a_path);

    Sprite(const Sprite &sprite);

    ~Sprite();

    void setPixel(const Point &p, Pixel pixel);

    Pixel *getImage() const;

    const Pixel &operator()(const Point &p) const;

    Pixel &operator()(const Point &p);

    Size getSize() const;

    int getChannels() const;

private:
    Pixel *image;
    Size size;
    int channels{};
    bool isStbBuffer{};
};

#endif