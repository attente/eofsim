/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "trail.hh"

#include "sdl.hh"

trail::trail (const trail &t)
: head (t.head),
  thickness (t.thickness),
  size (t.size),
  init (t.init)
{
  tail = new vector[size];

  for (int i = 0; i < size; i++)
    tail[i] = t.tail[i];
}

trail::trail (int    n,
              double x,
              double y,
              double z,
              double r,
              double g,
              double b,
              double a,
              double radius)
: thickness (radius),
  size (n),
  init (0)
{
  head.x = tracker (x);
  head.y = tracker (y);
  head.z = tracker (z);

  head.r = r;
  head.g = g;
  head.b = b;
  head.a = a;

  tail = new vector[size];

  for (int i = 0; i < size; i++)
    tail[i] = vector (x, y, z);
}

trail &
trail::operator= (const trail &t)
{
  if (&t == this)
    return *this;

  delete [] tail;

  head = t.head;
  size = t.size;
  init = t.init;

  tail = new vector[size];

  for (int i = 0; i < size; i++)
    tail[i] = t.tail[i];

  return *this;
}

void
trail::set_position (double x,
                     double y,
                     double z)
{
  vector pos (x, y, z);

  head.x = tracker (x);
  head.y = tracker (y);
  head.z = tracker (z);

  for (int i = 0; i < size; i++)
    tail[i] = pos;
}

void
trail::update (double dt)
{
  head.update (dt);
  tail[init++] = vector (head.x, head.y, head.z);
  init %= size;
}

void
trail::render () const
{
  glPointParameterf (GL_POINT_SIZE_MIN, thickness);
  glPointParameterf (GL_POINT_SIZE_MAX, thickness);

  glBegin (GL_POINTS);
  glEnable (GL_POINT_SPRITE);
  glPointSize (1);

  head.render (true);

  for (int i = 0; i < size; i++)
    {
      int j = (init + i) % size;

      bind_glow ();
      glColor4d (head.r, head.g, head.b, head.a * i / size);
      glVertex3d (tail[j].x, tail[j].y, tail[j].z);
    }

  for (int i = 0; i < size; i++)
    {
      int j = (init + i) % size;

      bind_bulb ();
      glColor4d (1, 1, 1, head.a * i / size);
      glVertex3d (tail[j].x, tail[j].y, tail[j].z);
    }

  glDisable (GL_POINT_SPRITE);
  glEnd ();
}

trail::~trail ()
{
  delete [] tail;
}
