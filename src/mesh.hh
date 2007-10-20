/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef MESH_HH
#define MESH_HH

#include "sdl.hh"

class mesh {
public:
    explicit mesh(const char *file);

    void render() const;

    GLuint list;
};

#endif
