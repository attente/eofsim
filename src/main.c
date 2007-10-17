#include <stdbool.h>
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

  physics_initialise (1000, 100, -200, 0);
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

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      return 0;

    graphics_render ();
    netsend_packet (net, &remote);

    {
      double x, y;
      physics_get_location (&x, &y);

      serial_write (fd, x, y, 0);
    }
  }

  return 0;
}
