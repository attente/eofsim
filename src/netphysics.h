#ifndef _netphysics_h_
#define _netphysics_h_

#include <stdbool.h>

#include "physics.h"
#include "net.h"

bool netphysics_read_packet (int fd);

#endif /* _netphysics_h_ */
