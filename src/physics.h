/*
 * Copyright © 2007 Ryan Lortie, William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

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
                        double dy,
                        int seed);
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

int physics_get_n_rings (void);
const double *physics_get_rings_horiz (void);
const double *physics_get_rings_vert (void);
int physics_get_serial (void);
double physics_get_time (void);
double physics_get_time_bonus (void);
double physics_get_next_ring (void);

#ifdef __cplusplus
}
#endif

#endif /* _physics_h_ */
