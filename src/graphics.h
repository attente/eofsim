/*
 * Copyright © 2007 Ryan Lortie, William Hua
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef _graphics_h_
#define _graphics_h_

#ifdef __cplusplus
extern "C" {
#endif

int graphics_initialise(void);
void graphics_destroy(void);
void graphics_render(void);
void graphics_mode(int m);

int graphics_get_mode (void);

void graphics_stop(void);
bool graphics_loop(void);
double graphics_delta(void);

void graphics_print(const char *s, double x, double y,
                         double c, double h, double v);

void graphics_fade (void);

#ifdef __cplusplus
}
#endif

#endif /* _graphics_h_ */
