/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include <assert.h>
#include <string.h>

#include "physics.h"
#include "netsend.h"

bool
netsend_packet (int fd, const net_addr *addr)
{
  struct net_state state;
  int n_rings;

  n_rings = physics_get_n_rings ();

  assert (n_rings * sizeof (double) == sizeof state.rings_horiz);
  assert (n_rings * sizeof (double) == sizeof state.rings_vert);

  physics_get_location (&state.x, &state.y);
  physics_get_direction (&state.dx, &state.dy);
  state.thrust = physics_get_thrust ();
  state.flaps = physics_get_flaps ();
  state.score = physics_get_score ();
  memcpy (state.rings_horiz, physics_get_rings_horiz(), sizeof state.rings_horiz);
  memcpy (state.rings_vert, physics_get_rings_vert(), sizeof state.rings_vert);
  state.serial = physics_get_serial ();

  return sendto (fd, &state, sizeof state, 0, (struct sockaddr *) addr, sizeof (struct sockaddr_in)) == sizeof state;
}
