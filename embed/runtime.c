#include <avr/interrupt.h>

#include "runtime.h"

void
send_byte (guint8 byte)
{
  while (!get_bit (avr_control.ucsr0a, UDRE0));
  avr_control.udr0 = byte;
}

void
state_error (void)
{
  send_byte ('X');
  for(;;);
}

void
timeout_error (void)
{
  send_byte ('!');
  for(;;);
}

volatile guint8 tick;

ISR(TIMER0_OVF_vect)
{
  tick++;
}

void
mainloop (void)
{
  guint8 start;

  start = tick;
  while (start == tick);

  while (true)
  {
    start = tick;

    one_iteration ();

    if (start != tick)
      /*timeout_error ()*/;

    while (start == tick);
  }
}

void
initialise (void)
{
  avr_control.tccr0b = _BV(CS01) | _BV(CS00);
  set_bit (avr_control.timsk0, TOIE0);
  sei ();

  avr_control.ubrr0 = 16000000/16/9600 - 1;
  avr_control.ucsr0b = _BV (TXEN0);

  clr_ddr (B, 0);
  set_port (B, 0);
  clr_ddr (B, 1);
  set_port (B, 1);
  clr_ddr (B, 2);
  set_port (B, 2);
  clr_ddr (B, 3);
  set_port (B, 3);
  clr_ddr (B, 4);
  set_port (B, 4);
  clr_ddr (B, 5);
  set_port (B, 5);
  clr_ddr (D, 7);
  set_port (D, 7);
/*
  set_bit (avr_control.tccr1b, CS11);
  set_bit (avr_control.tccr1b, CS10);
  set_bit (avr_control.tccr1a, WGM10);

  set_bit (avr_control.tccr2b, CS22);
  set_bit (avr_control.tccr2a, WGM20);
  */

  //set_ddr (D, 3);
  //set_bit (avr_control.tccr2a, COM2B1);

  //avr_control.ocr2b = 5;
}

int
main (void)
{
  initialise ();
  mainloop ();
}
