#ifndef _physics_h_
#define _physics_h_

#ifdef __cplusplus
extern "C" {
#else
#include <stdbool.h>
#endif

void physics_initialise(double  x,
                        double  y,
                        double dx,
                        double dy);
void physics_destroy(void);

double physics_get_degrees(void);
double physics_get_radians(void);

void physics_get_location(double *x, double *y);
void physics_get_direction(double *x, double *y);

int physics_get_thrust(void);
int physics_get_flaps(void);

void physics_set_thrust(int value);
void physics_set_flaps(int value);

bool physics_update(void);

double physics_get_score (void);
const char *physics_get_message (void);
void physics_set_message (const char *message);
void physics_landing_gear (void);
bool physics_is_shaking (void);

#ifdef __cplusplus
}
#endif

#endif /* _physics_h_ */
