/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef PARTICLE_HH
#define PARTICLE_HH

#include "tracker.hh"

class particle
{
  public:

    double size;
    tracker x, y, z;
    double r, g, b, a;

    void update (double dt);
    void render (bool ready) const;
};

void particle_init ();
void particle_exit ();

void bind_glow ();
void bind_bulb ();

#endif
