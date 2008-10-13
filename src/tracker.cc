/*
 * Copyright © 2007 William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include "tracker.hh"

#include <cmath>

const double EPS = 1E-12;

tracker::tracker (double z)
: x (z),
  y (z),
  v (0),
  a (0)
{
}

void
tracker::update (double dt)
{
  if (-EPS <= a && a <= EPS)
    {
      y += v * dt;
      return;
    }

  double dvdt = x < y ? -a : a;
  double disc = std::sqrt (v * v / 2 + dvdt * (x - y));
  double t = (-v + (x < y ? -disc : disc)) / dvdt;

  if (t >= dt)
    {
      double dv = dvdt * dt;

      y += (v + dv / 2) * dt;
      v += dv;
    }
  else if (t >= 0)
    {
      double dv = dvdt * t;

      y += (v + dv / 2) * dt;
      v += dv;

      dt -= t;
      dv = -dvdt * dt;

      y += (v + dv / 2) * dt;
      v += dv;
    }
  else
    {
      double dv = -dvdt * dt;

      y += (v + dv / 2) * dt;
      v += dv;
    }

  if (-EPS <= v && v <= EPS && x - y <= EPS && y - x <= EPS)
    y = x;
}

tracker::operator double () const
{
  return y;
}

tracker &
tracker::operator= (double z)
{
  x = z;

  return *this;
}

tracker &
tracker::operator= (const tracker &t)
{
  if (&t == this)
    return *this;

  x = t.x;
  y = t.y;
  v = t.v;
  a = t.a;

  return *this;
}
