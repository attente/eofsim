#include "physics.hh"
#include "plane.hh"

static plane *obj;

void physics_initialise(double  x,
                        double  y,
                        double dx,
                        double dy,
                        double  a) {
    obj = new plane(x, y, dx, dy, a);
    obj->start();
}

void physics_destroy() {
    delete obj;
}

void physics_get_location(double *x, double *y) {
    *x = obj->position().z;
    *y = obj->position().y;
}

void physics_get_direction(double *x, double *y) {
    *x = obj->direction().z;
    *y = obj->direction().y;
}

void physics_set_thrust(int value) {
    obj->engine(value);
}

void physics_set_flaps(int value) {
    obj->wings(value);
}

void physics_update() {
    obj->update();
}
