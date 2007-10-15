/*
 * Copyright © 2007 Ryan Lortie
 *
 * All rights reserved.
 */

#include "avr-control.h"

#include "pwmdecode.h"

#if 0
void
pwmdecode (void)
{
  static signed char count[3];
  static char iter;

  if (((++iter) & 31) == 0)
  {
    int i;
    
    for (i = 0; i < 3; i++)
    {
      serial_send ((count[i]/4) + 'm');
      count[i] = 0;
    }

    serial_send ('\n');
  }

  if (get_pin (B, 0))
  {
    if (count[0] < 0)
      count[0] = 0;
    count[0]++;
  }

  if (get_pin (D, 7))
  {
    if (count[0] > 0)
      count[0] = 0;
    count[0]--;
  }

  if (get_pin (B, 2))
  {
    if (count[1] < 0)
      count[1] = 0;
    count[1]++;
  }

  if (get_pin (B, 1))
  {
    if (count[1] > 0)
      count[1] = 0;
    count[1]--;
  }

  if (get_pin (B, 4))
  {
    if (count[2] < 0)
      count[2] = 0;
    count[2]++;
  }

  if (get_pin (B, 3))
  {
    if (count[2] > 0)
      count[2] = 0;
    count[2]--;
  }
}
#endif

void
pwmdecode_initialise (void)
{
  clr_ddr (D, 7);
  clr_port (D, 7);
  clr_ddr (B, 0);
  clr_port (B, 0);
  clr_ddr (B, 1);
  clr_port (B, 1);
  clr_ddr (B, 2);
  clr_port (B, 2);
  clr_ddr (B, 3);
  clr_port (B, 3);
  clr_ddr (B, 4);
  clr_port (B, 4);
}
