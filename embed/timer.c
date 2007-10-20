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

#include "timer.h"

volatile guint8 tick;

ISR (TIMER0_OVF_vect)
{
  tick++;
}

void
timer_wait (void)
{
  static guint8 last;

  while (tick == last);

  last = tick;
}

void
timer_initialise (void)
{
  avr_control.tccr0b = _BV(CS01);// | _BV(CS00);
  set_bit (avr_control.timsk0, TOIE0);
  sei ();
}
