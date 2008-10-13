/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "ring.hh"

#include <cstdlib>
#include <cmath>

const double EPS           = 1E-2;

const int    TRAILS        = 12;
const double SNAP_ACCEL    = 1000;
const double SMOOTH_ACCEL  = 5;
const double ROTATE_ACCEL  = 0.1;
const double NORMAL_RADIUS = 100;

ring::ring (const ring &cp)
: autonomous (cp.autonomous),
  a (cp.a),
  r (cp.r),
  y (cp.y),
  z (cp.z),
  trails (new trail[TRAILS])
{
  for (int i = 0; i < TRAILS; i++)
    trails[i] = cp.trails[i];
}

ring::ring (double horizontal,
            double vertical)
: autonomous (true),
  a (0),
  r (1),
  y (vertical),
  z (horizontal),
  trails (new trail[TRAILS])
{
  a.v = EPS;
  a.a = ROTATE_ACCEL;
  r.a = 0;

  for (int i = 0; i < TRAILS; i++)
    {
      trails[i].set_position (0 + (r + (i & 1)) * NORMAL_RADIUS *
                                std::cos (2 * M_PI * i / TRAILS),
                              y + (r + (i & 1)) * NORMAL_RADIUS *
                                std::sin (2 * M_PI * i / TRAILS),
                              z);

      trails[i].head.x.a = SNAP_ACCEL;
      trails[i].head.y.a = SNAP_ACCEL;
      trails[i].head.z.a = SMOOTH_ACCEL;

      trails[i].head.r = 0;
      trails[i].head.g = 0;
      trails[i].head.b = 0;

      if (6 * i <= TRAILS || 6 * i >= 5 * TRAILS)
        trails[i].head.r = 1;
      else if (3 * i < TRAILS)
        trails[i].head.r = 2 - 6.0 * i / TRAILS;
      else if (3 * i > 2 * TRAILS)
        trails[i].head.r = 6.0 * i / TRAILS - 4;

      if (6 * i >= TRAILS && 2 * i <= TRAILS)
        trails[i].head.g = 1;
      else if (3 * i < 2 * TRAILS)
        trails[i].head.g = 2 - std::fabs (6.0 * i / TRAILS - 2);

      if (2 * i >= TRAILS && 6 * i <= 5 * TRAILS)
        trails[i].head.b = 1;
      else if (3 * i > TRAILS)
        trails[i].head.b = 2 - std::fabs (6.0 * i / TRAILS - 4);
    }
}

void
ring::update (double dt)
{
  if (a.x - a.y >= 0 && a.x - a.y <= EPS)
    a.x -= 5 + std::rand () % 1000 / 100.0;
  else if (a.x - a.y >= -EPS && a.x - a.y <= 0)
    a.x += 5 + std::rand () % 1000 / 100.0;

  a.update (dt);

  r.x = 1 + std::fabs (z.v);
  r.update (dt);

  for (int i = 0; i < TRAILS; i++)
    {
      trails[i].head.x.x = 0 + (r + (i & 1)) * NORMAL_RADIUS *
                               std::cos (2 * M_PI * i / TRAILS + a * (i & 1 ? -1 : 1));
      trails[i].head.y.x = y + (r + (i & 1)) * NORMAL_RADIUS *
                               std::sin (2 * M_PI * i / TRAILS + a * (i & 1 ? -1 : 1));
      trails[i].head.x.y = trails[i].head.x.x;
      trails[i].head.y.y = trails[i].head.y.x;
      trails[i].update (dt);
    }
}

void
ring::render (double x) const
{
  for (int i = 0; i < TRAILS; i++)
    {
      trails[i].thickness = 256.0 / (1.0 + std::fabs (x - z) * 0.025);
      trails[i].render ();
    }
}

ring::~ring ()
{
  delete [] trails;
}
