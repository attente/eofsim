/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef SCENE_HH
#define SCENE_HH

#include "sdl.hh"
#include "mesh.hh"
#include "texture.hh"
#include "ring.hh"

const int STARS = 100;

class scene {
public:
    scene();
    ~scene();

    void stop();
    bool loop() const;
    void render(int mode = 0) const;

private:
    bool running;

    texture backdrop;
    texture ground;
    texture runway;
    texture shadow;
    texture stills;
    GLuint list;
    mesh tower;
    mesh obj;
    particle stars[STARS];

    mutable ring *rings;
    mutable int walkx, walky;
    mutable int serial;
};

#endif
