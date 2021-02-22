#include "Render.h"

Render::Render(const std::string &a_path) {
    if ((staticImage = new Sprite(a_path)) != nullptr) {
        dynamicImage = new Sprite(*staticImage);
        sizeOfRendering = staticImage->GetSize();
        channels = staticImage->GetChannels();
    }
}

Render::Render(const Pixel &backgroundColor, const Size &size, int a_channels) : sizeOfRendering(size) {
    staticImage = new Sprite(backgroundColor, size, a_channels);
    dynamicImage = new Sprite(backgroundColor, size, a_channels);
}

Render::Render(const Sprite &sprite) {
    staticImage = new Sprite(sprite);
    dynamicImage = new Sprite(sprite);
    sizeOfRendering = staticImage->GetSize();
    channels = staticImage->GetChannels();
}

void Render::DrawStatic() {
    DrawSprite({0, 0}, *staticImage);
}

void Render::AddLayer(const Sprite &sprite, const Point &leftBottom) {
    for (int i = leftBottom.y; i < leftBottom.y + sprite.GetSize().height; i++) {
        for (int j = leftBottom.x; j < leftBottom.x + sprite.GetSize().width; j++) {
            auto currPixel = sprite({j - leftBottom.x, i - leftBottom.y});
            if (currPixel.a == 255) {
                staticImage->SetPixel({j, i}, currPixel);
                dynamicImage->SetPixel({j, i}, currPixel);
            }
        }
    }
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
        return staticImage->GetImage()[sizeOfRendering.width * p.y + p.x];
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
        return PutPixel(p, staticImage->GetImage()[sizeOfRendering.width * p.y + p.x]);
    }
    return false;
}

void Render::DrawSquare(const Point &p, const Size &size, const Pixel &color) {
    for (int i = p.y; i < p.y + size.height; ++i) {
        for (int j = p.x; j < p.x + size.width; ++j) {
            PutPixel({j, i}, color);
        }
    }
}

void Render::FreeSquare(const Point &p, const Size &size) {
    for (int i = p.y; i < p.y + size.height; ++i) {
        for (int j = p.x; j < p.x + size.width; ++j) {
            PutSourcePixel({j, i});
        }
    }
}

void Render::DrawSprite(const Point &p, const Sprite &sprite) {
    Size s = sprite.GetSize();
    //std::cout << s.width << " " << s.height << std::endl;
    auto tmpImage = sprite.GetImage();
    for (int i = 0; i < s.height; ++i) {
        for (int j = 0; j < s.width; ++j) {
            if (tmpImage[s.width * i + j].a != 0) {
                PutPixel({p.x + j, p.y + i}, tmpImage[s.width * i + j]);
            }
        }
    }
}

void Render::DrawObject(const GameObject &obj) {
    DrawSprite(obj.GetPosition(), obj.GetSprite());
}

Render::~Render() {
    delete staticImage;
    delete dynamicImage;
}

Size Render::GetSizeOfRender() const {
    return sizeOfRendering;
}

int Render::GetChannels() const {
    return channels;
}

Sprite *Render::GetDynamicImage() const {
    return dynamicImage;
}

Sprite *Render::GetSourceImage() const {
    return staticImage;
}
