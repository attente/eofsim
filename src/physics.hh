#ifndef PHYSICS_HH
#define PHYSICS_HH

void physics_initialise(double  x,
                        double  y,
                        double dx,
                        double dy,
                        double  a);
void physics_destroy(void);

void physics_get_location(double *x, double *y);
void physics_get_direction(double *x, double *y);

void physics_set_thrust(int value);
void physics_set_flaps(int value);

void physics_update(void);

#endif
