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

    trail (int    n,
           double x,
           double y,
           double z,
           double r,
           double g,
           double b,
           double a,
           double radius);

    trail &operator= (const trail &t);

    void update (double dt);
    void render () const;

    ~trail ();

  private:

    vector   *tail;
    int       size;
    int       init;

    double    thickness;
};

#endif
