/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef FONT_HH
#define FONT_HH

#include "texture.hh"

class font {
public:
    explicit font(const char *file);

    void print(const char *s, double x, double y,
               double c = 1, double h = 0, double v = 0) const;

    ~font();

private:
    double width(const char *s) const;

    texture *img;
    double lo, hi;
    double l[257];
    int rows, cols;
};

#endif
