#include "physics.h"
#include "plane.hh"

#include <cmath>

static plane *obj;

void physics_initialise(double  x,
                        double  y,
                        double dx,
                        double dy) {
  if (obj)
    delete obj;

  obj = new plane(x, y, dx, dy);
  obj->start();
}

void physics_destroy() {
    delete obj;
}

double physics_get_degrees() {
    return physics_get_radians() * 180 / M_PI;
}

double physics_get_radians() {
    if (obj->direction().length() <= 1E-6)
        return 0;

    if (obj->direction().z > -1E6) {
        if (obj->direction().y > -1E6)
            return atan2(obj->direction().y, -obj->direction().z) + M_PI;
        else
            return atan2(obj->direction().y, -obj->direction().z) - M_PI;
    }

    return atan2(obj->direction().y, -obj->direction().z);
}

void physics_get_location(double *x, double *y) {
    *x = obj->position().z;
    *y = obj->position().y;
}

void physics_get_direction(double *x, double *y) {
    *x = obj->direction().z;
    *y = obj->direction().y;
}

int physics_get_thrust() {
    return obj->engine();
}

int physics_get_flaps() {
    return obj->wings();
}

void physics_set_thrust(int value) {
    obj->engine(value);
}

void physics_set_flaps(int value) {
    obj->wings(value);
}

bool physics_update() {
    return obj->update();
}

double
physics_get_score (void)
{
  return obj->get_score();
}

const char *
physics_get_message (void)
{
  return obj->message;
}

void
physics_set_message (const char *message)
{
  obj->set_message (message, 100);
}

void
physics_landing_gear (void)
{
  obj->landing_gear ();
}

bool
physics_is_shaking (void)
{
  return obj->is_shaking ();
}
