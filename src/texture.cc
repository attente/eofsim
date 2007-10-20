/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "texture.hh"

#include <iostream>
using std::cerr;

static SDL_PixelFormat *format();
static void select(int w1, int h1, int &w2, int &h2);

texture::texture(const char *file) : id(0) {
    if (file == NULL) return;
    SDL_Surface *src(IMG_Load(file));
    if (src == NULL) return;

    SDL_Surface *img(SDL_ConvertSurface(src, format(), SDL_SWSURFACE));
    int w1(src->w), h1(src->h), w2, h2;
    select(w1, h1, w2, h2);
    SDL_FreeSurface(src);

    if (img == NULL || w2 <= 0 || h2 <= 0) return;

    unsigned int *data(NULL);
    bool lock(SDL_MUSTLOCK(img));
    bool unlock(lock && !SDL_LockSurface(img));

    try {
        data = new unsigned int[w2 * h2];

        if (lock && !unlock || gluScaleImage(GL_RGBA,
            w1, h1, GL_UNSIGNED_BYTE, img->pixels,
            w2, h2, GL_UNSIGNED_BYTE, data))
                throw data;
    }
    catch (...) {
        if (unlock) SDL_UnlockSurface(img);
        SDL_FreeSurface(img);
        delete [] data;
        return;
    }

    if (unlock) SDL_UnlockSurface(img);
    SDL_FreeSurface(img);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w2, h2, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, data);

    delete [] data;
}

texture::operator GLuint() const {
    return id;
}

texture::~texture() {
    glDeleteTextures(1, &id);
}

static SDL_PixelFormat *format() {
    static SDL_PixelFormat fmt;
    static bool ready(false);
    if (ready) return &fmt;

    fmt.Rloss = 0;
    fmt.Gloss = 0;
    fmt.Bloss = 0;
    fmt.Aloss = 0;

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    fmt.Rshift = 24;
    fmt.Gshift = 16;
    fmt.Bshift = 8;
    fmt.Ashift = 0;
#else
    fmt.Rshift = 0;
    fmt.Gshift = 8;
    fmt.Bshift = 16;
    fmt.Ashift = 24;
#endif

    fmt.Rmask = 0xff >> fmt.Rloss << fmt.Rshift;
    fmt.Gmask = 0xff >> fmt.Gloss << fmt.Gshift;
    fmt.Bmask = 0xff >> fmt.Bloss << fmt.Bshift;
    fmt.Amask = 0xff >> fmt.Aloss << fmt.Ashift;

    Uint32 mask(fmt.Rmask | fmt.Gmask | fmt.Bmask | fmt.Amask);

    fmt.BytesPerPixel = mask < 0x00000001 ? 0 :
                        mask < 0x00000100 ? 1 :
                        mask < 0x00010000 ? 2 :
                        mask < 0x01000000 ? 3 :
                                            4 ;

    fmt.BitsPerPixel = fmt.BytesPerPixel << 3;

    ready = true;
    return &fmt;
}

static int shrink(int x) {
    x >>= 1;
    x |= x >>  1;
    x |= x >>  2;
    x |= x >>  4;
    x |= x >>  8;
    x |= x >> 16;
    return x + 1;
}

static int expand(int x) {
    x--;
    x |= x >>  1;
    x |= x >>  2;
    x |= x >>  4;
    x |= x >>  8;
    x |= x >> 16;
    return x + 1;
}

static void select(int w1, int h1, int &w2, int &h2) {
    w2 = w1 < 0x40000000 ? expand(w1) : shrink(w1);
    h2 = h1 < 0x40000000 ? expand(h1) : shrink(h1);
}
