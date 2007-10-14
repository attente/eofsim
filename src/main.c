#include <stdbool.h>
#include <SDL.h>

#include "graphics.h"
#include "physics.h"
#include "serial.h"

int
main (void)
{
  int fd;

  graphics_initialise ();

  physics_initialise (1000, 100, -200, 0);
  physics_set_thrust (8);
  physics_set_flaps (0);
  
  fd = serial_open ();

  while (serial_read (fd))
  {
    SDL_Event event;

    if (SDL_PollEvent(&event) && event.type == SDL_QUIT)
      return 0;

    graphics_render ();
  }

  return 0;
}
