/*
 * Copyright © 2007 Ryan Lortie
 *
 * All rights reserved.
 */

#include "avr-control.h"
#include "softserial.h"
#include "pwmdecode.h"
#include "serial.h"
#include "timer.h"

int
main (void)
{
  softserial_initialise ();
  pwmdecode_initialise ();
  serial_initialise ();
  timer_initialise ();

  while (true)
    softserial_update ();
}
