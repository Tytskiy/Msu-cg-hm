#include <iostream>
#include "Render.h"

Render::Render(const std::string &a_path) {
    if ((sourceImage = new Sprite(a_path)) != nullptr) {
        dynamicImage = new Sprite(*sourceImage);
        sizeOfRendering = sourceImage->GetSize();
        channels = sourceImage->GetChannels();
    }
}

Render::Render(const Pixel &backgroundColor, const Size &size, int a_channels) : sizeOfRendering(size) {
    sourceImage = new Sprite(backgroundColor, size, a_channels);
    dynamicImage = new Sprite(backgroundColor, size, a_channels);
}

Render::Render(const Level &level) {
    sourceImage = new Sprite(*level.GetMainSprite());
    dynamicImage = new Sprite(*level.GetMainSprite());
    sizeOfRendering = sourceImage->GetSize();
    channels = sourceImage->GetChannels();
}

Render::Render(const Sprite &image) {
    sourceImage = new Sprite(image);
    dynamicImage = new Sprite(image);
    sizeOfRendering = sourceImage->GetSize();
    channels = sourceImage->GetChannels();
}

bool Render::IsValidPixel(const Point &p) const {
    if (0 < p.x and p.x < sizeOfRendering.width and 0 < p.y and p.y < sizeOfRendering.height) {
        return true;
    }
    return false;
}

Pixel Render::GetDynamicPixel(const Point &p) const {
    if (IsValidPixel(p)) {
        return dynamicImage->GetImage()[sizeOfRendering.width * p.y + p.x];
    }
    return Pixel{255, 255, 255, 255};
}

Pixel Render::GetSourcePixel(const Point &p) const {
    if (IsValidPixel(p)) {
        return sourceImage->GetImage()[sizeOfRendering.width * p.y + p.x];
    }
    return Pixel{255, 255, 255, 255};
}

bool Render::PutPixel(const Point &p, const Pixel &pix) {
    if (IsValidPixel(p)) {
        dynamicImage->GetImage()[sizeOfRendering.width * p.y + p.x] = pix;
        return true;
    }
    return false;
}

bool Render::PutSourcePixel(const Point &p) {
    if (IsValidPixel(p)) {
        return PutPixel(p, sourceImage->GetImage()[sizeOfRendering.width * p.y + p.x]);
    }
    return false;
}

void Render::DrawSquare(const Point &p, const Size &size, const Pixel &color) {
    for (int i = p.x; i < p.x + size.width; ++i) {
        for (int j = p.y; j < p.y + size.height; ++j) {
            PutPixel({i, j}, color);
        }
    }
}

void Render::FreeSquare(const Point &p, const Size &size) {
    for (int i = p.x; i < p.x + size.width; ++i) {
        for (int j = p.y; j < p.y + size.height; ++j) {
            PutSourcePixel({i, j});
        }
    }
}

void Render::DrawSpriteSquare(const Point &p, const Sprite &sprite) {
    Size s = sprite.GetSize();
    std::cout << s.width << " " << s.height << std::endl;
    auto tmpImage = sprite.GetImage();
    for (int i = 0; i < s.width; ++i) {
        for (int j = 0; j < s.height; ++j) {
            if (tmpImage[s.width * j + i].a != 0) {
                PutPixel({p.x + i, p.y + j}, tmpImage[s.width * j + i]);
            }
        }
    }
}

Render::~Render() {
    delete sourceImage;
    delete dynamicImage;
}

Size Render::GetSizeOfRender() const { return sizeOfRendering; }

int Render::GetChannels() const { return channels; }

Sprite *Render::DynamicImage() const { return dynamicImage; }

Sprite *Render::SourceImage() const { return sourceImage; }