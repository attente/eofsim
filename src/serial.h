#ifndef _serial_h_
#define _serial_h_

#include <stdbool.h>

bool serial_read (int fd);
int serial_open (void);
void serial_write (int fd, int a, int b, int c);

#endif /* _serial_h_ */
