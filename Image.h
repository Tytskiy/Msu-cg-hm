#ifndef MAIN_IMAGE_H
#define MAIN_IMAGE_H

#include <string>

constexpr int tileSize = 16;  //кратно 2

struct Pixel {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

struct Image {
    explicit Image(const std::string &a_path);
    Image(int a_width, int a_height, int a_channels, Pixel backgroundColor = {0, 0, 0, 0});

    int Save(const std::string &a_path);

    int Width() const { return width; }
    int Height() const { return height; }
    int Channels() const { return channels; }
    size_t Size() const { return size; }
    Pixel *DynamicImage() const { return dynamicImage; }
    Pixel *SourceImage() const { return sourceImage; }
    bool isValidPixel(int x, int y) const;
    Pixel GetDynamicPixel(int x, int y) const;
    Pixel GetSourcePixel(int x, int y) const;
    bool PutPixel(int x, int y, const Pixel &pix);
    bool PutSourcePixel(int x, int y);
    void DrawSquare(int x, int y, int width, int height, Pixel color);
    void FreeSquare(int x, int y, int width, int height);

    ~Image();

   private:
    int width = -1;
    int height = -1;
    int channels = 3;
    size_t size = 0;
    Pixel *dynamicImage = nullptr;
    Pixel *sourceImage = nullptr;
    bool self_allocated = false;
};

#endif  // MAIN_IMAGE_H
