#include "paint.hpp"
#include "utils/utils.hpp"


Paint::Image::Image() : BM(nullptr) {}

Paint::Image::Image(const Image& image) {
    this->BFH = image.BFH;
    this->BIH = image.BIH;
    this->BM = new BGR*[image.BIH.height];
    for (int i = 0; i < image.BIH.height; i++) {
        BM[i] = new BGR[image.BIH.width];
        for (int j = 0; j < image.BIH.width; j++) BM[i][j] = image.BM[i][j];
    }
}

Paint::Image::~Image() {
    if (this->BM) {
        for (int i = 0; i < BIH.height; i++) delete[] BM[i];
        delete[] BM;
    }
}

Paint::Image& Paint::Image::operator=(const Image& image) {
    if (this->BM) {
        for (int i = 0; i < BIH.height; i++) delete[] BM[i];
        delete[] this->BM;
    }

    this->BFH = image.BFH;
    this->BIH = image.BIH;
    this->BM = new BGR*[image.BIH.height];
    for (int i = 0; i < image.BIH.height; i++) {
        BM[i] = new BGR[image.BIH.width];
        for (int j = 0; j < image.BIH.width; j++) BM[i][j] = image.BM[i][j];
    }
    return *this;
}

bool Paint::Image::load(std::string path) {
    std::ifstream file(path, std::ios_base::binary);

    if (!file.bad()) {
        file.read((char*)&BFH, sizeof(BitmapFileHeader));
        if ((BFH.signature != 19778) || (BFH.reserved1 != 0) || (BFH.reserved2 != 0)) {
            std::cout << "Файл не поддерживается!\n";
            file.close();
            return false;
        }

        file.read((char*)&BIH, sizeof(BitmapInfoHeader));
        if ((BIH.headerSize != 40) || (BIH.bitsPerPixel != 24) || (BIH.colorsInColorTable != 0) || (BIH.importantColorCount != 0)) {
            std::cout << "Файл не поддерживается!\n";
            file.close();
            return false;
        }

        char temp;
        BM = new BGR*[BIH.height];
        for (int i = 0; i < BIH.height; i++) {
            BM[i] = new BGR[BIH.width];
            file.read((char*)BM[i], BIH.width * sizeof(BGR));
            for (int i = 0; i < (4 - (BIH.width * 3) % 4) % 4; i++) file.read(&temp, sizeof(char));
        }

        file.close();
        return true;
    }
    std::cout << "Не верный путь до файла!\n";
    return false;
}

bool Paint::Image::save(std::string path) {
    if (!BM) throw std::invalid_argument("# Image.save: Empty BitMap!");
    std::ofstream file(path, std::ios_base::binary);

    if (!file.bad()) {
        file.write((char*)&BFH, sizeof(BitmapFileHeader));
        file.write((char*)&BIH, sizeof(BitmapInfoHeader));

        int H = BIH.height;
        int W = BIH.width;

        for (int i = 0; i < H; i++) {
            file.write((char*)BM[i], W * sizeof(BGR));
            char temp = '\0';
            for (int i = 0; i < (4 - (W * 3) % 4) % 4; i++) file.write(&temp, sizeof(char));
        }

        file.close();
        return true;
    }
    std::cout << "Не верный путь до файла!\n";
    return false;
}


std::vector<Paint::Image> Paint::cut_the_crap(CutLines lines, const Image& image) {
    std::vector<Image> images;
    if (lines.x_num < 1 || lines.y_num < 1) throw std::invalid_argument("# Paint::cut_the_crap: Cut lines should be larger then zero!");

    Image n_image(image);
    int H = n_image.BIH.height /= lines.y_num;
    int W = n_image.BIH.width /= lines.x_num;

    for (int i = 0; i < lines.y_num; i++) {
        for (int j = 0; j < lines.x_num; j++) {
            n_image.BM = new BGR*[H];
            for (int k = 0; k < H; k++) {
                n_image.BM[k] = new BGR[W];
                for (int l = 0; l < W; l++)  n_image.BM[k][l] = image.BM[i * H + k][j * W + l];
            }
            images.push_back(n_image);
        }
    }
    return images;
}

Paint::Image Paint::set_component(Component color, const Image& image) {
    Image n_image(image);

    for (int i = 0; i < n_image.BIH.height; i++) {
        for (int j = 0; j < n_image.BIH.width; j++) {
            switch (color.index) {
            case 'r':
                n_image.BM[i][j].r = color.value;
                break;
            case 'g':
                n_image.BM[i][j].g = color.value;
                break;
            case 'b':
                n_image.BM[i][j].b = color.value;
                break;
            }
        }
    }
    return n_image;
}

Paint::Image Paint::put_circle(Circle circle, const Image& image) {
    Image n_image(image);

    int x0, y0, rad_b, rad_s;
    BGR l_color, f_color;

    if (circle.x2) {
        x0 = (circle.x1 + circle.x2) / 2;
        y0 = (circle.y1 + circle.y2) / 2;
        rad_b = x0 - circle.x1;
        rad_s = rad_b - circle.width;
        l_color = circle.l_color;
        if (circle.f_flag) f_color = circle.f_color;
    }
    else {
        x0 = circle.x0;
        y0 = circle.y0;
        rad_b = circle.rad_b;
        rad_s = rad_b - circle.width;
        l_color = circle.l_color;
        if (circle.f_flag) f_color = circle.f_color;
    }

    for (int i = 0; i < n_image.BIH.height; i++) {
        for (int j = 0; j < n_image.BIH.width; j++) {
            if ((circle.f_flag) && ((x0 - j) * (x0 - j) + (y0 - i) * (y0 - i) - rad_b * rad_b < 0))
                n_image.BM[i][j] = f_color;
            if (((x0 - j) * (x0 - j) + (y0 - i) * (y0 - i) - rad_b * rad_b < rad_b) && ((x0 - j) * (x0 - j) + (y0 - i) * (y0 - i) - rad_s * rad_s > -rad_s))
                n_image.BM[i][j] = l_color;
        }
    }
    return n_image;
}

Paint::Image Paint::put_rectangle(Rectangle rect, const Image& image) {
    Image n_image(image);

    int x1 = rect.x1, x2 = rect.x2, y1 = rect.y1, y2 = rect.y2, x_to = rect.x_to, y_to = rect.y_to;
    int H = n_image.BIH.height;
    int W = n_image.BIH.width;

    if ((x1 < 0) || (x1 > W) || (y1 < 0) || (y1 > H) || (x2 < x1) || (x2 > W) || (y2 < y1) || (y2 > H))
        throw std::invalid_argument("# Paint::put_rectangle: Rectangle should be inside image!");

    BGR** new_BM = new BGR*[y2 - y1];
    for (int i = 0; i < y2 - y1; i++) {
        new_BM[i] = new BGR[x2 - x1];
        for (int j = 0; j < (x2 - x1); j++) {
            new_BM[i][j] = n_image.BM[i + y1][j + x1];
        }
    }
    for (int i = 0; i < y2 - y1; i++) {
        for (int j = 0; j < x2 - x1; j++) {
            if ((i + y_to < H) && (i + y_to > -1) && (j + x_to < W) && (j + x_to > -1))
                n_image.BM[i + y_to][j + x_to] = new_BM[i][j];
        }
    }
    return n_image;
}

std::ostream& Paint::operator<<(std::ostream& out, const BitmapFileHeader& bfh) {
    return out << bfh.signature << '\n' << bfh.filesize << '\n' << bfh.reserved1 << '\n' << bfh.reserved2 << '\n' << bfh.pixelArrOffset << '\n';
}

std::ostream& Paint::operator<<(std::ostream& out, const BitmapInfoHeader& bih) {
    out << bih.headerSize << '\n' << bih.width << '\n' << bih.height << '\n' << bih.planes << '\n';
    out << bih.bitsPerPixel << '\n' << bih.compression << '\n' << bih.imageSize << '\n' << bih.xPixelsPerMeter << '\n';
    out << bih.yPixelsPerMeter << '\n' << bih.colorsInColorTable << '\n' << bih.importantColorCount << '\n';
    return out;
}

std::ostream& Paint::operator<<(std::ostream& out, const BGR& bgr) {
    return out << bgr.b << '\n' << bgr.g << '\n' << bgr.r << '\n';
}