/*
 * Copyright © 2007 Ryan Lortie
 *
 * All rights reserved.
 */

#ifndef _softserial_h_
#define _softserial_h_

#include "avr-gtypes.h"

void       softserial_queue_set   (guint8 values[3]);
void       softserial_queue_off   (void);

void       softserial_update      (void);
void       softserial_initialise  (void);

#endif /* _softserial_h_ */
