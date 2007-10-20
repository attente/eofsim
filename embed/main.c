/*
 * Copyright © 2007 Ryan Lortie
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of version 3 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * See the included COPYING file for more information.
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
  {
    pwmdecode_iteration ();
    timer_wait ();
    softserial_update ();
  }
}
