#include <sys/poll.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>

#include "graphics.h"
#include "physics.h"
#include "netsend.h"
#include "serial.h"

int
main (void)
{
  net_addr remote;
  int net;
  int fd;

  physics_initialise (10000, 1000, -200, 0);
  physics_set_thrust (0);
  physics_set_flaps (0);

  graphics_initialise ();

  fd = serial_open ();
  net = net_open ();

  net_addr_set (&remote, "172.20.0.249");

  while (1)
  {
    SDL_Event event;

    serial_read (fd);

    poll(NULL, 0, 10);
    physics_update ();

    if (SDL_PollEvent(&event) &&
        (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN &&
                         event.key.keysym.sym == SDLK_ESCAPE)))
      return 0;

    graphics_render ();
    netsend_packet (net, &remote);

    {
      double x, y, dx, dy, angle;
      physics_get_location (&x, &y);
      physics_get_direction (&dx, &dy);

      angle = 75 - 180/M_PI * atan (dy/dx);
      printf ("%f/%f is %f\n", dy, dx, angle);

      serial_write (fd, y / 10.0, x / 100.0, angle);
    }
  }

  return 0;
}
