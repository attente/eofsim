/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#include <sys/poll.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <SDL.h>

#include "graphics.h"
#include "physics.h"
#include "netsend.h"
#include "serial.h"

static bool randomised;

static void
publish_the_physics (int       serial,
                     int       net,
                     net_addr *remote)
{
  double x, y, dx, dy, angle;

  netsend_packet (net, remote);

  physics_get_location (&x, &y);
  physics_get_direction (&dx, &dy);
  angle = physics_get_degrees ();

  serial_write (serial, y / 10.0, x / 100.0, 75 + angle);
}

static void
reset_the_physics (bool regenerate)
{
  static double start = 10000;

  if (randomised && regenerate)
  {
    srand (time (NULL));
    start = 7000 + (rand () % 7001);
  }

  physics_initialise (start, 1000, -200, 0, 1);
  physics_set_thrust (0);
  physics_set_flaps (0);
}

static char
check_sdl (void)
{
  SDL_Event event;

  if (!SDL_PollEvent(&event))
    return 0;

  if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
                       event.key.keysym.sym == SDLK_ESCAPE))
    exit (0);

  if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE)
    return ' ';

  return 0;
}

int
main (int argc, char **argv)
{
  net_addr remote;
  int serial;
  int net;

  graphics_initialise ();

  serial = serial_open ();
  net = net_open ();

  if (argc != 1)
  {
    if (argc != 2)
    {
      fprintf (stderr, "only 1 or 0 args\n");
      return 1;
    }

    if (strcmp (argv[1], "--final"))
    {
      fprintf (stderr, "unrecognised option\n");
      return 1;
    }
  }
  else
    randomised = true;

  printf ("randomised: %d\n", randomised);

  while (serial_ready (serial))
    serial_read (serial);
  net_addr_set (&remote, "10.0.0.2");

  while (true)
  {
    bool ended;

    /* wait for user */
    reset_the_physics (true);
    physics_set_message ("READY");
    publish_the_physics (serial, net, &remote);
    graphics_render ();

    while (!serial_ready (serial))
      check_sdl ();

    reset_the_physics (false);
    ended = false;
    while (!ended)
    {
      serial_read (serial);
      poll (NULL, 0, 10);
      ended = physics_update ();
      publish_the_physics (serial, net, &remote);
      check_sdl ();
      graphics_render ();
    }

    while (check_sdl () != ' ')
      poll (NULL, 0, 10);

    while (serial_ready (serial))
      serial_read (serial);
  }
}
