#include "Sprite.h"
#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION

#include "stb_image_write.h"

Sprite::Sprite(Pixel color, Size size, int channels)
        : size(size), channels(channels), isStbBuffer(false) {
    image = new Pixel[size.width * size.height];
    FillArray(image, size.width * size.height, color);
}

Sprite::Sprite(const Pixel *pixels, Size size, int channels) : size(size), channels(channels), isStbBuffer(false) {
    image = CopyFromPointer(pixels, size.width * size.height);
}

Sprite::Sprite(const std::string &a_path) : size() {
    if ((image = (Pixel *) stbi_load(a_path.c_str(), &size.width, &size.height, &channels, sizeof(Pixel))) != nullptr) {
        isStbBuffer = true;
    }
}

Sprite::Sprite(const Sprite &sprite) : size() {
    size = sprite.size;
    image = CopyFromPointer(sprite.image, size.width * size.height);
    channels = sprite.channels;
}

Sprite::~Sprite() {
    if (isStbBuffer) {
        stbi_image_free(image);
    } else {
        delete[] image;
    }
}

Pixel *Sprite::GetImage() const { return image; }

Size Sprite::GetSize() const { return size; }

int Sprite::GetChannels() const { return channels; }
