/*
 * Copyright © 2007 Ryan Lortie
 *
 * All rights reserved.
 */

#include "avr-control.h"
#include "softserial.h"

#include "serial.h"

void
serial_send (guint8 byte)
{
  while (!get_bit (avr_control.ucsr0a, UDRE0));
  avr_control.udr0 = byte;
}

ISR(USART_RX_vect)
{
  static guint8 offset = 3;
  static guint8 buffer[3];

  if (offset > 2)
  {
    switch (UDR0)
    {
      case '*':
        /* start new data packet */
        offset = 0;
        break;

      case '-':
        /* powersave */
        softserial_queue_off ();
        break;
    }
  }
  else
  {
    buffer[offset++] = UDR0;

    if (offset == 3)
      softserial_queue_set (buffer);
  }
}

void
serial_initialise (void)
{
  avr_control.ubrr0 = 16000000/16/9600 - 1;
  avr_control.ucsr0b = _BV (TXEN0) | _BV (RXEN0) | _BV(RXCIE0);
  sei ();

  serial_send ('&');
}
