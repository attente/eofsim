#ifndef _netsend_h_
#define _netsend_h_

#include <netinet/in.h>
#include <stdbool.h>

#include "net.h"

bool netsend_packet (int fd, const net_addr *addr);

#endif /* _netsend_h_ */
