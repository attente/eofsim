#ifndef _serial_h_
#define _serial_h_

#include <stdbool.h>

bool serial_read (int fd);
int serial_open (void);

#endif /* _serial_h_ */
