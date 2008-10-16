/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include <sys/socket.h>
#include <math.h>

#include "netphysics.h"

static struct net_state state;

double physics_get_degrees(void) {
    return physics_get_radians() * 180 / M_PI;
}

double physics_get_radians(void) {
    return atan2(state.y, -state.x);
}

void
physics_get_direction (double *dxptr,
                       double *dyptr)
{
  *dxptr = state.dx;
  *dyptr = state.dy;
}

void
physics_get_location (double *xptr,
                      double *yptr)
{
  *xptr = state.x;
  *yptr = state.y;
}

int
physics_get_thrust (void)
{
  return state.thrust;
}

int
physics_get_flaps (void)
{
  return state.flaps;
}

double
physics_get_score(void)
{
  return state.score;
}

bool physics_is_shaking(void) {
  return false;
}

bool
netphysics_read_packet (int fd)
{
  return recv (fd, &state, sizeof state, MSG_TRUNC) == sizeof state;
}

const char *
physics_get_message (void)
{
  return NULL;
}

const double *
physics_get_rings_horiz (void)
{
  return state.rings_horiz;
}

const double *
physics_get_rings_vert (void)
{
  return state.rings_vert;
}

int
physics_get_n_rings (void)
{
  return NET_RINGS;
}

int
physics_get_serial (void)
{
  return state.serial;
}

double
physics_get_time (void)
{
  return state.time;
}

double
physics_get_time_bonus (void)
{
  return 1.;
}
