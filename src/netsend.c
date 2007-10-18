#include "physics.h"
#include "netsend.h"

bool
netsend_packet (int fd, const net_addr *addr)
{
  struct net_state state;

  physics_get_location (&state.x, &state.y);
  physics_get_direction (&state.dx, &state.dy);
  state.thrust = physics_get_thrust ();
  state.flaps = physics_get_flaps ();
  state.score = physics_get_score ();

  return sendto (fd, &state, sizeof state, 0, (struct sockaddr *) addr, sizeof (struct sockaddr_in)) == sizeof state;
}
