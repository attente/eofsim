/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef _net_h_
#define _net_h_

#include <netinet/in.h>
#include <stdbool.h>

#define NET_RINGS 8

struct net_state
{
  double x, y, dx, dy;
  int thrust, flaps;
  double rings_horiz[NET_RINGS];
  double rings_vert[NET_RINGS];
  int serial;
  double time;
  double score;
  double time_bonus;
};

typedef struct sockaddr_in net_addr;

int      net_open        (void);
int      net_bind        (void);
bool     net_addr_set    (net_addr   *addr,
                          const char *ip);

#endif /* _net_h_ */
