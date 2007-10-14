#ifndef PHYSICS_HH
#define PHYSICS_HH

void physics_initialise(double  x,
                        double  y,
                        double dx,
                        double dy);
void physics_destroy(void);

void physics_get_location(double *x, double *y);
void physics_get_direction(double *x, double *y);

int physics_get_thrust(void);
int physics_get_flaps(void);

void physics_set_thrust(int value);
void physics_set_flaps(int value);

void physics_update(void);

#endif
