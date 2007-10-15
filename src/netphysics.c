#include <sys/socket.h>

#include "netphysics.h"

static struct net_state state;

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

bool
netphysics_read_packet (int fd)
{
  return recv (fd, &state, sizeof state, MSG_TRUNC) == sizeof state;
}
