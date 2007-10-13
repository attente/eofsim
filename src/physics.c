#include <math.h>

#include "physics.h"

static double x, y;
static double dx, dy;

void
physics_initialise (void)
{
  x = 20000;
  y = 2000;
  dx = 1;
  dy = 0;
}

double
physics_get_angle (void)
{
  return atan (dy / dx);
}

void
physics_get_position (double *xptr,
                      double *yptr)
{
  *xptr = x;
  *yptr = y;
}

void
physics_get_velocity (double *dxptr,
                      double *dyptr)
{
  *dxptr = dx;
  *dyptr = dy;
}

static void
physics_add_speed (double amount)
{
  double angle = physics_get_angle ();

  dx += cos (angle) * amount;
  dy += sin (angle) * amount;
}

double
physics_get_speed (void)
{
  return sqrt (dy * dy + dx * dx);
}

void
physics_step (int thrust, int flaps)
{
  /* update position
   *
   * update for thrust
   * update for flaps
   * update for gravity
   * update for air resistance
   *
   * consider: ground
   */

  x += dx;
  y += dy;

  physics_add_speed (thrust);
}
