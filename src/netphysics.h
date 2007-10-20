/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef _netphysics_h_
#define _netphysics_h_

#include <stdbool.h>

#include "physics.h"
#include "net.h"

bool netphysics_read_packet (int fd);

#endif /* _netphysics_h_ */
