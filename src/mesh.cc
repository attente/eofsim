/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "mesh.hh"
#include "vector.hh"

#include <fstream>

mesh::mesh(const char *file) {
    std::ifstream input(file);
    vector p[4], n;

    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glBegin(GL_QUADS);

    while (input.good()) {
        input >> p[0].x >> p[0].y >> p[0].z;
        input >> p[1].x >> p[1].y >> p[1].z;
        input >> p[2].x >> p[2].y >> p[2].z;
        input >> p[3].x >> p[3].y >> p[3].z;

        if (!input.good()) break;
        n = (p[1] - p[0]).cross(p[2] - p[0]);
        n *= 1.0 / n.length();

        glNormal3d(n.x, n.y, n.z);
        glVertex3d(p[0].x, p[0].y, p[0].z);
        glVertex3d(p[1].x, p[1].y, p[1].z);
        glVertex3d(p[2].x, p[2].y, p[2].z);
        glVertex3d(p[3].x, p[3].y, p[3].z);
    }

    glEnd();
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEndList();
}

void mesh::render() const {
    glCallList(list);
}
