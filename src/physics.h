#ifndef _physics_h_
#define _physics_h_

#ifdef __cplusplus
extern "C" {
#endif

double     physics_get_angle        (void);
double     physics_get_speed        (void);

void       physics_get_position     (double *xptr,
                                     double *yptr);
void       physics_get_velocity     (double *dxptr,
                                     double *dyptr);

void       physics_initialise       (void);
void       physics_step             (int     thrust,
                                     int     flaps);

#ifdef __cplusplus
}
#endif

#endif /* _physics_h_ */
