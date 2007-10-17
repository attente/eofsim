/*
 * Copyright © 2007 Ryan Lortie
 *
 * All rights reserved.
 */

#include <string.h>

#include "avr-control.h"

#include "pwmdecode.h"
#include "serial.h"

static void
pwmdecode_emit (guint8 values[3])
{
  static guint8 last_values[3];

  if (!memcmp (values, last_values, sizeof values))
    return;

  memcpy (last_values, values, sizeof values);

  serial_send (values[0]);
  serial_send (values[1]);
  serial_send (values[2]);
  serial_send ('\n');
}

void
pwmdecode_iteration (void)
{
  static guint8 iterations;
  static int count[3];
  guint8 values[3];

  if ((++iterations) == 0)
  {
    int i;
   
    for (i = 0; i < 3; i++)
    {
      int sign;

      sign = count[i] < 0;

      if (sign)
        count[i] = -count[i];

      count[i] += 16;
      count[i] /= 32;

      if (sign)
        count[i] = -count[i];

      values[i] = count[i] + 'm';
      count[i] = 0;
    }

    pwmdecode_emit (values);
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
