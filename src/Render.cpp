#include "Render.h"

Render::Render(const std::string &a_path) {
    if ((staticImage = new Sprite(a_path)) != nullptr) {
        dynamicImage = new Sprite(*staticImage);
        sizeOfRendering = staticImage->getSize();
        channels = staticImage->getChannels();
    }
}

Render::Render(const Pixel &backgroundColor, const Size &size, int a_channels) : sizeOfRendering(size) {
    staticImage = new Sprite(backgroundColor, size, a_channels);
    dynamicImage = new Sprite(backgroundColor, size, a_channels);
}

Render::Render(const Sprite &sprite) {
    staticImage = new Sprite(sprite);
    dynamicImage = new Sprite(sprite);
    sizeOfRendering = staticImage->getSize();
    channels = staticImage->getChannels();
}

void Render::drawStatic() {
    drawSprite({0, 0}, *staticImage);
}

void Render::addLayer(const Sprite &sprite, const Point &topLeft) {
    for (int i = 0; i < sprite.getSize().height; i++) {
        for (int j = 0; j < sprite.getSize().width; j++) {
            auto currPixel = sprite({j, i});
            if (currPixel.a == 255) {
                staticImage->setPixel({j + topLeft.x, i + topLeft.y}, currPixel);
                dynamicImage->setPixel({j + topLeft.x, i + topLeft.y}, currPixel);
            }
        }
    }
}

bool Render::isValidPixel(const Point &p) const {
    if (0 < p.x and p.x < sizeOfRendering.width and 0 < p.y and p.y < sizeOfRendering.height) {
        return true;
    }
    return false;
}

Pixel Render::getDynamicPixel(const Point &p) const {
    if (isValidPixel(p)) {
        return dynamicImage->getImage()[sizeOfRendering.width * p.y + p.x];
    }
    return Pixel{255, 255, 255, 255};
}

Pixel Render::getSourcePixel(const Point &p) const {
    if (isValidPixel(p)) {
        return staticImage->getImage()[sizeOfRendering.width * p.y + p.x];
    }
    return Pixel{255, 255, 255, 255};
}

bool Render::putPixel(const Point &p, const Pixel &pix) {
    if (isValidPixel(p)) {
        dynamicImage->getImage()[sizeOfRendering.width * p.y + p.x] = pix;
        return true;
    }
    return false;
}

bool Render::putSourcePixel(const Point &p) {
    if (isValidPixel(p)) {
        return putPixel(p, staticImage->getImage()[sizeOfRendering.width * p.y + p.x]);
    }
    return false;
}

void Render::drawSquare(const Point &p, const Size &size, const Pixel &color) {
    for (int i = p.y; i < p.y + size.height; ++i) {
        for (int j = p.x; j < p.x + size.width; ++j) {
            putPixel({j, i}, color);
        }
    }
}

void Render::freeSquare(const Point &p, const Size &size) {
    for (int i = p.y; i < p.y + size.height; ++i) {
        for (int j = p.x; j < p.x + size.width; ++j) {
            putSourcePixel({j, i});
        }
    }
}

void Render::drawSprite(const Point &p, const Sprite &sprite) {
    Size s = sprite.getSize();
    //std::cout << s.width << " " << s.height << std::endl;
    auto tmpImage = sprite.getImage();
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            if (tmpImage[s.width * i + j].a != 0) {
                putPixel({p.x + j, p.y + i}, tmpImage[s.width * i + j]);
            }
        }
    }
}

void Render::drawObject(const GameObject &obj) {
    drawSprite(obj.getPosition(), obj.getSprite());
}

Render::~Render() {
    delete staticImage;
    delete dynamicImage;
}

Size Render::getSizeOfRender() const {
    return sizeOfRendering;
}

int Render::getChannels() const {
    return channels;
}

Sprite *Render::getDynamicImage() const {
    return dynamicImage;
}

Sprite *Render::getSourceImage() const {
    return staticImage;
}
