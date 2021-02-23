#include "Sprite.h"
#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

Sprite::Sprite() = default;;


Sprite::Sprite(Pixel color, Size size, int channels) : size(size), channels(channels), isStbBuffer(false) {
    image = new Pixel[size.width * size.height];
    fillArray(image, size.width * size.height, color);
}

Sprite::Sprite(const Pixel *pixels, Size size, int channels) : size(size), channels(channels), isStbBuffer(false) {
    image = copyFromPointer(pixels, size.width * size.height);
}

Sprite::Sprite(const std::string &a_path) : size() {
    if ((image = (Pixel *) stbi_load(a_path.c_str(), &size.width, &size.height, &channels, sizeof(Pixel))) != nullptr) {
        isStbBuffer = true;
    }
}

Sprite::Sprite(const Sprite &sprite) : size() {
    size = sprite.size;
    image = copyFromPointer(sprite.image, size.width * size.height);
    channels = sprite.channels;
}

Sprite::~Sprite() {
    if (isStbBuffer) {
        stbi_image_free(image);
    } else {
        delete[] image;
    }
}

void Sprite::setPixel(const Point &p, Pixel pixel) {
    image[size.width * p.y + p.x] = pixel;
}

Pixel *Sprite::getImage() const {
    return image;
}


Size Sprite::getSize() const {
    return size;
}

int Sprite::getChannels() const {
    return channels;
}


const Pixel &Sprite::operator()(const Point &p) const {
    return image[size.width * p.y + p.x];
}

Pixel &Sprite::operator()(const Point &p) {
    return image[size.width * p.y + p.x];
}
