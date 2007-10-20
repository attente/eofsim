/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef _netsend_h_
#define _netsend_h_

#include <netinet/in.h>
#include <stdbool.h>

#include "net.h"

bool netsend_packet (int fd, const net_addr *addr);

#endif /* _netsend_h_ */
