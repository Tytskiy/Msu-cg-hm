#include "Render.h"

// я старался не делать вот такое.. прости меня мир..
void RGBtoHSV(float fR, float fG, float fB, float &fH, float &fS, float &fV) {
    float fCMax = std::max(std::max(fR, fG), fB);
    float fCMin = std::min(std::min(fR, fG), fB);
    float fDelta = fCMax - fCMin;

    if (fDelta > 0) {
        if (fCMax == fR) {
            fH = 60 * (fmod(((fG - fB) / fDelta), 6));
        } else if (fCMax == fG) {
            fH = 60 * (((fB - fR) / fDelta) + 2);
        } else if (fCMax == fB) {
            fH = 60 * (((fR - fG) / fDelta) + 4);
        }

        if (fCMax > 0) {
            fS = fDelta / fCMax;
        } else {
            fS = 0;
        }

        fV = fCMax;
    } else {
        fH = 0;
        fS = 0;
        fV = fCMax;
    }

    if (fH < 0) {
        fH = 360 + fH;
    }
}


void HSVtoRGB(float &fR, float &fG, float &fB, float fH, float fS, float fV) {
    float fC = fV * fS; // Chroma
    float fHPrime = fmod(fH / 60.0, 6);
    float fX = fC * (1 - fabs(fmod(fHPrime, 2) - 1));
    float fM = fV - fC;

    if (0 <= fHPrime && fHPrime < 1) {
        fR = fC;
        fG = fX;
        fB = 0;
    } else if (1 <= fHPrime && fHPrime < 2) {
        fR = fX;
        fG = fC;
        fB = 0;
    } else if (2 <= fHPrime && fHPrime < 3) {
        fR = 0;
        fG = fC;
        fB = fX;
    } else if (3 <= fHPrime && fHPrime < 4) {
        fR = 0;
        fG = fX;
        fB = fC;
    } else if (4 <= fHPrime && fHPrime < 5) {
        fR = fX;
        fG = 0;
        fB = fC;
    } else if (5 <= fHPrime && fHPrime < 6) {
        fR = fC;
        fG = 0;
        fB = fX;
    } else {
        fR = 0;
        fG = 0;
        fB = 0;
    }

    fR += fM;
    fG += fM;
    fB += fM;
}


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
    drawSprite(*staticImage, {0, 0});
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
    if (0 <= p.x and p.x < sizeOfRendering.width and 0 <= p.y and p.y < sizeOfRendering.height) {
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

void Render::drawSprite(const Sprite &sprite, const Point &p) {
    Size s = sprite.getSize();
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
    drawSprite(obj.getSprite(), obj.getPosition());
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

void Render::dimming(float brightness) {
    for (int i = 0; i < sizeOfRendering.height; i++) {
        for (int j = 0; j < sizeOfRendering.width; j++) {
            auto img = getDynamicPixel({j, i});
            float h, s, v;
            float r = img.r / 255.0;
            float g = img.g / 255.0;
            float b = img.b / 255.0;
            RGBtoHSV(r, g, b, h, s, v);
            HSVtoRGB(r, g, b, h, s, brightness * v);
            Pixel blending = {(uint8_t) (r * 255.0), (uint8_t) (g * 255.0), (uint8_t) (b * 255.0), 255};
            putPixel({j, i}, blending);
        }
    }
}

void Render::blur(int power) {
    if (power < 3) power = 3;
    if (power % 2 == 0) power++;
    float matrix[power][power];
    for (int i = 0; i < power; i++) {
        for (int j = 0; j < power; j++) {
            matrix[i][j] = 1.0 / (power * power);
        }
    }
    if (!blurShit)
        blurShit = copyFromPointer(dynamicImage->getImage(), sizeOfRendering.width * sizeOfRendering.height);

    for (int i = 0; i < sizeOfRendering.height; i++) {
        for (int j = 0; j < sizeOfRendering.width; j++) {
            Pixel newPixel{0, 0, 0, 255};
            for (int k = -power / 2; k <= power / 2; k++) {
                for (int g = -power / 2; g <= power / 2; g++) {
                    if (isValidPixel({j + g, i + k})) {
                        newPixel = newPixel + blurShit[(i + k) * sizeOfRendering.width + j + g] *
                                              matrix[k + power / 2][g + power / 2];
                    }
                }
            }
            blurShit[i * sizeOfRendering.width + j] = newPixel;
            dynamicImage->setPixel({j, i}, newPixel);
        }
    }
}

