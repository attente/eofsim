#include "font.hh"
#include "sdl.hh"

#include <iostream>
using std::cerr;

#include <fstream>

font::font(const char *file) {
    std::ifstream input(file);
    const int length(1024);
    char buffer[length];

    input.getline(buffer, length);
    img = new texture(buffer);
    input >> rows >> cols;
    input >> lo >> hi;
    input >> l[256];

    for (int i(0); i < 256; i++)
        input >> l[i];
}

void font::print(const char *s, double x, double y,
                      double c, double h, double v) const {
    double wd(c * width(s));
    double ht(c * (hi - lo));

    x -= h * wd;
    y -= v * ht;

    glColor4d(0, 0, 0, 1);
    glBindTexture(GL_TEXTURE_2D, *img);

    for (; *s; s++) {
        int i(*s < 0 ? *s + 256 : *s);

        glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2d(l[i] / cols, lo / rows);
        glVertex2d(x, y);
        glTexCoord2d(l[i] / cols, hi / rows);
        glVertex2d(x, y + ht);
        x += c * (l[i + 1] - l[i]);
        glTexCoord2d(l[i + 1] / cols, lo / rows);
        glVertex2d(x, y);
        glTexCoord2d(l[i + 1] / cols, hi / rows);
        glVertex2d(x, y + ht);
        glEnd();
    }

    glBindTexture(GL_TEXTURE_2D, 0);
}

font::~font() {
    delete img;
}

double font::width(const char *s) const {
    double w(0);

    for (; *s; s++) {
        int i(*s < 0 ? *s + 256 : *s);
        w += l[i + 1] - l[i];
    }

    return w;
}
