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

  /*
  while (true)
  {
    if (get_pin (B, 3))
      serial_send ('x');
    else
      serial_send ('X');

    int i;
    for (i = 0; i < 1000; i++)
      timer_wait ();

    if (get_pin (B, 4))
      serial_send ('y');
    else
      serial_send ('Y');

    for (i = 0; i < 1000; i++)
      timer_wait ();
  }*/

  while (true)
  {
    pwmdecode_iteration ();
    timer_wait ();
    softserial_update ();
  }
}
