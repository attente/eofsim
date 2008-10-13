/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef TRAIL_HH
#define TRAIL_HH

#include "vector.hh"
#include "particle.hh"

class trail
{
  public:

    particle head;

    double   thickness;

    trail (const trail &t);

    explicit trail (int    n = 20,
                    double x = 0,
                    double y = 0,
                    double z = 0,
                    double r = 1,
                    double g = 1,
                    double b = 1,
                    double a = 1,
                    double radius = 16);

    trail &operator= (const trail &t);

    void set_position (double x,
                       double y,
                       double z);

    void update (double dt);
    void render () const;

    ~trail ();

  private:

    vector   *tail;
    int       size;
    int       init;
};

#endif
