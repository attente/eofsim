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
#include "graphics.h"

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
      if (graphics_get_mode () != 2)
        {
          glPointParameterf (GL_POINT_SIZE_MIN, size);
          glPointParameterf (GL_POINT_SIZE_MAX, size);

          glEnable (GL_POINT_SMOOTH);
          glEnable (GL_POINT_SPRITE);

          glBegin (GL_POINTS);
        }
      else
        glBegin (GL_QUADS);
    }

  glColor4d (r, g, b, a);
  bind_glow ();
  glTexCoord2d (0, 0);
  glVertex3d (x, y - size, z - size);
  glTexCoord2d (0, 1);
  glVertex3d (x, y - size, z + size);
  glTexCoord2d (1, 1);
  glVertex3d (x, y + size, z + size);
  glTexCoord2d (1, 0);
  glVertex3d (x, y + size, z - size);

  glColor4d (1, 1, 1, a);
  bind_bulb ();
  glTexCoord2d (0, 0);
  glVertex3d (x, y - size, z - size);
  glTexCoord2d (0, 1);
  glVertex3d (x, y - size, z + size);
  glTexCoord2d (1, 1);
  glVertex3d (x, y + size, z + size);
  glTexCoord2d (1, 0);
  glVertex3d (x, y + size, z - size);

  if (!ready)
    {
      if (graphics_get_mode () != 2)
        {
          glDisable (GL_POINT_SMOOTH);
          glDisable (GL_POINT_SPRITE);
        }

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
