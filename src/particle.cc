/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "particle.hh"

#include "sdl.hh"
#include "texture.hh"

static texture *glow;
static texture *bulb;

void
particle::update (double dt)
{
  x.update (dt);
  y.update (dt);
  z.update (dt);
}

void
particle::render (bool ready) const
{
  if (!ready)
    {
      glBegin (GL_POINTS);
      glEnable (GL_POINT_SPRITE);
    }

  glPushMatrix ();

  bind_glow ();
  glColor4d (r, g, b, a);
  glVertex3d (x, y, z);

  bind_bulb ();
  glColor4d (1, 1, 1, a);
  glVertex3d (x, y, z);

  glPopMatrix ();

  if (!ready)
    {
      glDisable (GL_POINT_SPRITE);
      glEnd ();
    }
}

void
particle_init ()
{
  GLfloat coeffs[] = { 1, 0, 0 };

  glTexEnvi (GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);

  glPointParameterf (GL_POINT_FADE_THRESHOLD_SIZE, 1);
  glPointParameterfv (GL_POINT_DISTANCE_ATTENUATION, coeffs);

  glow = new texture ("../data/glow.png");
  bulb = new texture ("../data/bulb.png");
}

void
particle_exit ()
{
  delete glow;
  delete bulb;
}

void
bind_glow ()
{
  glBindTexture (GL_TEXTURE_2D, *glow);
}

void
bind_bulb ()
{
  glBindTexture (GL_TEXTURE_2D, *bulb);
}
