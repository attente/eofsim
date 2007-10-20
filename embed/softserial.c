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

#define cs(x)   x##_port (D, 2)
#define clk(x)  x##_port (D, 3)
#define a(x)    x##_port (D, 4)
#define b(x)    x##_port (D, 5)
#define c(x)    x##_port (D, 6)

static void
softserial_clock_pulse (void)
{
  clk (set);
  clk (clr);
}

static void
softserial_byte_all (guint8 cmd)
{
  guint8 i;

  for (i = 0x80; i > 0; i >>= 1)
  {
    if (cmd & i)
    {
      a (set);
      b (set);
      c (set);
    }
    else
    {
      a (clr);
      b (clr);
      c (clr);
    }

    softserial_clock_pulse ();
  }
}

static void
softserial_byte_each (guint8 values[3])
{
  guint8 a, b, c;
  guint8 i;

  a = values[0];
  b = values[1];
  c = values[2];

  for (i = 0x80; i > 0; i >>= 1)
  {
    if (a & i)
      a (set);
    else
      a (clr);

    if (b & i)
      b (set);
    else
      b (clr);

    if (c & i)
      c (set);
    else
      c (clr);

    softserial_clock_pulse ();
  }
}

static void
softserial_set (guint8 values[3])
{
  cs (clr);
  softserial_byte_all (0x11);        /* xx01xx01 */
  softserial_byte_each (values);
  cs (set);
}

static void
softserial_off (void)
{
  cs (clr);
  softserial_byte_all (0x20);        /* xx10xx00 */
  softserial_byte_all (0x00);        /* xxxxxxxx */
  cs (set);
}

static guint8 queued_cmd;
static guint8 queued_values[3];

void
softserial_queue_set (guint8 values[3])
{
  queued_values[0] = values[0];
  queued_values[1] = values[1];
  queued_values[2] = values[2];
  queued_cmd = 1;
}

void
softserial_queue_off (void)
{
  queued_cmd = 2;
}

void
softserial_update (void)
{
  cli ();

  switch (queued_cmd)
  {
    case 1:
      softserial_set (queued_values);
      break;

    case 2:
      softserial_off ();
      break;
  }

  queued_cmd = 0;

  sei ();
}

void
softserial_initialise (void)
{
  /* cs, clk */
  set_ddr (D, 2);
  set_ddr (D, 3);

  /* data ports: a, b, c */
  set_ddr (D, 4);
  set_ddr (D, 5);
  set_ddr (D, 6);
}
