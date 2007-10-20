/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
 */

#ifndef _softserial_h_
#define _softserial_h_

#include "avr-gtypes.h"

void       softserial_queue_set   (guint8 values[3]);
void       softserial_queue_off   (void);

void       softserial_update      (void);
void       softserial_initialise  (void);

#endif /* _softserial_h_ */
