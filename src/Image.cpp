#include "Image.h"

#include <iostream>

#include "utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

Image::Image(const std::string &a_path) {
    if ((sourceImage = (Pixel *)stbi_load(a_path.c_str(), &width, &height, &channels, sizeof(Pixel))) != nullptr) {
        size = width * height * channels;
        dynamicImage = CopyFromPointer(sourceImage, width * height);
    }
}

Image::Image(int a_width, int a_height, int a_channels, Pixel backgroundColor) {
    sourceImage = new Pixel[a_width * a_height]{};
    dynamicImage = new Pixel[a_width * a_height]{};
    FillArray(sourceImage, a_width * a_height, backgroundColor);
    FillArray(dynamicImage, a_width * a_height, backgroundColor);

    if (dynamicImage != nullptr) {
        width = a_width;
        height = a_height;
        size = a_width * a_height * a_channels;
        channels = a_channels;
        self_allocated = true;
    }
}

int Image::Save(const std::string &a_path) {
    auto extPos = a_path.find_last_of('.');
    if (a_path.substr(extPos, std::string::npos) == ".png" || a_path.substr(extPos, std::string::npos) == ".PNG") {
        stbi_write_png(a_path.c_str(), width, height, channels, dynamicImage, width * channels);
    } else if (a_path.substr(extPos, std::string::npos) == ".jpg" ||
               a_path.substr(extPos, std::string::npos) == ".JPG" ||
               a_path.substr(extPos, std::string::npos) == ".jpeg" ||
               a_path.substr(extPos, std::string::npos) == ".JPEG") {
        stbi_write_jpg(a_path.c_str(), width, height, channels, dynamicImage, 100);
    } else {
        std::cerr << "Unknown file extension: " << a_path.substr(extPos, std::string::npos) << "in file name" << a_path
                  << "\n";
        return 1;
    }

    return 0;
}
bool Image::isValidPixel(int x, int y) const {
    if (0 < x and x < width and 0 < y and y < height) {
        return true;
    }
    return false;
}
Pixel Image::GetDynamicPixel(int x, int y) const {
    if (isValidPixel(x, y)) {
        return dynamicImage[width * y + x];
    }
    return Pixel{255, 255, 255, 255};
}

Pixel Image::GetSourcePixel(int x, int y) const {
    if (isValidPixel(x, y)) {
        return sourceImage[width * y + x];
    }
    return Pixel{255, 255, 255, 255};
}
bool Image::PutPixel(int x, int y, const Pixel &pix) {
    if (isValidPixel(x, y)) {
        dynamicImage[width * y + x] = pix;
        return true;
    }
    return false;
}
bool Image::PutSourcePixel(int x, int y) {
    if (isValidPixel(x, y)) {
        return PutPixel(x, y, sourceImage[width * y + x]);
    }
    return false;
}
void Image::DrawSquare(int x, int y, int width, int height, Pixel color) {
    for (int i = y - height / 2; i <= y + height / 2; ++i) {
        for (int j = x - width / 2; j <= x + width / 2; ++j) {
            PutPixel(j, i, color);
        }
    }
}
void Image::FreeSquare(int x, int y, int width, int height) {
    for (int i = y - height / 2; i <= y + height / 2; ++i) {
        for (int j = x - width / 2; j <= x + width / 2; ++j) {
            PutSourcePixel(j, i);
        }
    }
}
Image::~Image() {
    if (self_allocated) {
        delete[] sourceImage;
    } else {
        delete[] dynamicImage;
        stbi_image_free(sourceImage);
    }
}