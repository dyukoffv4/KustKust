#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "lib/terminal.hpp"


namespace Paint {
#pragma pack(push, 1)

    struct BitmapFileHeader {
        unsigned short signature;
        unsigned int filesize;
        unsigned short reserved1;
        unsigned short reserved2;
        unsigned int pixelArrOffset;
    };

    struct BitmapInfoHeader {
        unsigned int headerSize;
        unsigned int width;
        unsigned int height;
        unsigned short planes;
        unsigned short bitsPerPixel;
        unsigned int compression;
        unsigned int imageSize;
        unsigned int xPixelsPerMeter;
        unsigned int yPixelsPerMeter;
        unsigned int colorsInColorTable;
        unsigned int importantColorCount;
    };

    struct BGR {
        unsigned char b;
        unsigned char g;
        unsigned char r;
    };

    struct Rectangle {
        int x1;
        int y1;
        int x2;
        int y2;
        int x_to;
        int y_to;
    };

    struct CutLines {
        int x_num;
        int y_num;
    };

    struct Component {
        char index;
        int value;
    };

    struct Circle {
        int x0;
        int y0;
        int rad_b;
        int width;
        BGR l_color;
        int f_flag;
        BGR f_color;
    };

#pragma pack(pop)

    class Image {
    public:
        BitmapFileHeader BFH;
        BitmapInfoHeader BIH;
        BGR **BM;

        Image();
        Image(const Image& image);
        ~Image();

        Image& operator=(const Image& image);

        bool load(std::string path);
        bool save(std::string path);
    };

    std::vector<Image> cut_the_crap(CutLines lines, const Image& image);

    Image set_component(Component color, const Image& image);

    Image put_circle(Circle circle, const Image& image);

    Image put_rectangle(Rectangle rectangle, const Image& image);

    std::ostream &operator<<(std::ostream &out, const BitmapFileHeader &bfh);

    std::ostream &operator<<(std::ostream &out, const BitmapInfoHeader &bih);

    std::ostream &operator<<(std::ostream &out, const BGR &bgr);
}