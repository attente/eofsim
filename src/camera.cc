/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "camera.hh"
#include "sdl.hh"

camera::camera() {
    const double angle(120),
                 ratio(4.0 / 3.0),
                 near(1E-3), far(1E9);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angle, ratio, near, far);
}

void camera::rotate(double rx, double ry) {
    y = z.rotate(y, rx);
    vector w(y.cross(z));
    y = w.rotate(y, ry);
    z = w.rotate(z, ry);
}

void camera::move(const vector &d) {
    x += d.x * y.cross(z) + d.y * y + d.z * z;
}

void camera::position() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(x.x            , x.y            , x.z            ,
              x.x + y.x      , x.y + y.y      , x.z + y.z      ,
                        + z.x,           + z.y,           + z.z);
}
