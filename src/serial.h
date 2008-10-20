/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef _serial_h_
#define _serial_h_

#include <stdbool.h>

bool serial_read (int fd);
int serial_open (void);
void serial_write (int fd, double a, double b, double c);
bool serial_ready (int fd);
bool serial_discard (int fd);

#endif /* _serial_h_ */
