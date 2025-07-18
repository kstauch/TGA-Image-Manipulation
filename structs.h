#pragma once
#include <vector>
using namespace std;


struct Header {
    char idLength;
    char colorMapType;
    char dataTypeCode;
    short colorMapOrigin;
    short colorMapLength;
    char colorMapDepth;
    short xOrigin;
    short yOrigin;
    short width;
    short height;
    char bitsPerPixel;
    char imageDescriptor;
};

struct Pixel {
    unsigned char blue;
    unsigned char green;
    unsigned char red;
    Pixel() : blue(0), green(0), red(0) {}
    Pixel(const unsigned char b, const unsigned char g, const unsigned char r) : blue(b), green(g), red(r) {}
};

struct Image {
    Header header;
    vector<Pixel> pixels = {};
    Image() {
        pixels.reserve(262144);
    }
};
