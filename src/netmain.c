#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <SDL.h>

#include "netphysics.h"
#include "graphics.h"

int
main (void)
{
  int fd;

  fd = net_bind ();

  if (fd < 0)
  {
    perror ("bind");
    return 1;
  }

  graphics_initialise ();

  while (netphysics_read_packet (fd))
  {
    SDL_Event event;

    if (SDL_PollEvent(&event) &&
        (event.type == SDL_QUIT || event.type == SDL_KEYDOWN &&
                         event.key.keysym.sym == SDLK_ESCAPE))
      return 0;

    graphics_render ();
  }

  return 0;
}
