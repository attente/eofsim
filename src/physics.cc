/*
 * Copyright © 2007 Ryan Lortie, William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "physics.h"
#include "plane.hh"

#include <sys/time.h>
#include <cmath>

static plane *obj;
static int on_ring;
static double score;
static double rings_vert[8];
static double rings_horiz[8];
static double start_time;
static int serial;

double now (void)
{
  struct timeval tv;

  gettimeofday (&tv, NULL);

  return tv.tv_sec + tv.tv_usec / 1000000.;
}

void physics_initialise(double  x,
                        double  y,
                        double dx,
                        double dy,
                        int    random_seed) {
  int i;

  if (obj)
    delete obj;

  score = 0.;
  on_ring = 0;

  srand (random_seed);
  for (i = 0; i < 8; i++)
    rings_horiz[i] = 9000 - 1000 * i,
    rings_vert[i] = rand() % 401 + 800;
  start_time = now ();
  serial = start_time * 10;

  obj = new plane(x, y, dx, dy);
  obj->start();
}

void physics_destroy() {
    delete obj;
}

double physics_get_degrees() {
    return physics_get_radians() * 180 / M_PI;
}

double physics_get_radians() {
    if (obj->direction().length() <= 1E-6)
        return 0;

    return atan2(obj->direction().y, -obj->direction().z);
}

void physics_get_location(double *x, double *y) {
    *x = obj->position().z;
    *y = obj->position().y;
}

void physics_get_direction(double *x, double *y) {
    *x = obj->direction().z;
    *y = obj->direction().y;
}

int physics_get_thrust() {
    return obj->engine();
}

int physics_get_flaps() {
    return obj->wings();
}

void physics_set_thrust(int value) {
    obj->engine(value);
}

void physics_set_flaps(int value) {
    obj->wings(value);
}

bool
physics_update()
{
  bool status;

  if (on_ring == 8)
    return false;

  status = obj->update();

  if (obj->position().z < rings_horiz[on_ring])
    {
      static char message[100];
      double delta;
      double pts;

      delta = fabs (obj->position().y - rings_vert[on_ring]);
      if (delta > 20)
        pts = 1000 - 10 * delta;
      else
        pts = 1000;

      if (pts > 0)
        {
          sprintf (message, "%.1fm -- +%.1fpoints", delta, pts);
          score += pts;
        }
      else
        sprintf (message, "%.1fm -- no points", delta);

      obj->set_message (message, 100);
      on_ring++;
    }

  return status;
}

double
physics_get_score (void)
{
  return score;
}

const char *
physics_get_message (void)
{
  return obj->message;
}

void
physics_set_message (const char *message)
{
  obj->set_message (message, 100);
}

void
physics_landing_gear (void)
{
  obj->landing_gear ();
}

bool
physics_is_shaking (void)
{
  return obj->is_shaking ();
}

const double *
physics_get_rings_horiz (void)
{
  return rings_horiz;
}

const double *
physics_get_rings_vert (void)
{
  return rings_vert;
}

int
physics_get_n_rings (void)
{
  return 8;
}

int
physics_get_serial (void)
{
  return serial;
}

double
physics_get_time (void)
{
  return now() - start_time;
}
