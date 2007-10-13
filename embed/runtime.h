#ifndef _runtime_h_
#define _runtime_h_

#include <avr/io.h>
#include "avr-control.h"

#define packed __attribute__ ((packed))

void send_byte (guint8 byte);
void state_error (void);

/* you must implement: */
void one_iteration (void);

#endif /* _runtime_h_ */
