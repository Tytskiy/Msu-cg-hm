#ifndef MAIN_SPRITE_H
#define MAIN_SPRITE_H

#include "primitive.h"

#include <string>


struct Sprite {
    explicit Sprite(Pixel color, Size size, int channels = 4);

    explicit Sprite(const Pixel *pixels, Size size, int channel = 4);

    explicit Sprite(const std::string &a_path);

    Sprite(const Sprite &sprite);

    ~Sprite();

    Pixel *GetImage() const;

    Size GetSize() const;

    int GetChannels() const;

private:
    Pixel *image;
    Size size;
    int channels{};
    bool isStbBuffer{};
};

#endif