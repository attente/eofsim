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
  physics_set_thrust (8);
  physics_set_flaps (0);

  graphics_initialise ();

  fd = serial_open ();
  net = net_open ();

  net_addr_set (&remote, "127.0.0.1");

  while (serial_read (fd))
  {
    SDL_Event event;

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      return 0;

    graphics_render ();
    netsend_packet (net, &remote);
  }

  return 0;
}
