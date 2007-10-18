#ifndef _net_h_
#define _net_h_

#include <netinet/in.h>
#include <stdbool.h>

struct net_state
{
  double x, y, dx, dy;
  int thrust, flaps;
  double score;
};

typedef struct sockaddr_in net_addr;

int      net_open        (void);
int      net_bind        (void);
bool     net_addr_set    (net_addr   *addr,
                          const char *ip);

#endif /* _net_h_ */
