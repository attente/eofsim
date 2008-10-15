/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef RING_HH
#define RING_HH

#include "tracker.hh"
#include "trail.hh"

class ring
{
  public:

    bool autonomous;

    ring (const ring &cp);

    ring (double horizontal = 0,
          double vertical = 0);

    void set_position (double horizontal,
                       double vertical);

    void update (double dt);
    void render (double x) const;

    ~ring ();

  private:

    tracker  a, r;
    tracker  y, z;
    trail   *trails;
};

#endif
