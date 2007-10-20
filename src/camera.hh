/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef CAMERA_HH
#define CAMERA_HH

#include "vector.hh"

class camera {
public:
    camera();

    void rotate(double rx, double ry);
    void move(const vector &d);
    void position() const;

    vector x, y, z;
};

#endif
