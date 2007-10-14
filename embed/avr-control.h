#include "avr-gtypes.h"

enum
{
  AVR_X = 13,
  AVR_Y = 14,
  AVR_Z = 15
};

typedef union
{
  guint8  r[32];
  guint16 w[16];
} AVRRegisterFile;

enum
{
  AVR_PORTB,
  AVR_PORTC,
  AVR_PORTD
};

typedef struct
{
  guint8 pin;
  guint8 ddr;
  guint8 port;
} AVRPort;

typedef struct
{
  /* 0x00 */
  AVRRegisterFile reg;

  /* 0x20 */
  guint8  res0x20;
  guint8  res0x21;
  guint8  res0x22;
  AVRPort port[3];
  guint8  res0x2c;
  guint8  res0x2d;
  guint8  res0x2e;
  guint8  res0x2f;
  guint8  res0x30;
  guint8  res0x31;
  guint8  res0x32;
  guint8  res0x33;
  guint8  res0x34;
  guint8  tifr0;
  guint8  tifr1;
  guint8  tifr2;
  guint8  res0x38;
  guint8  res0x39;
  guint8  res0x4a;
  guint8  pcifr;
  guint8  eifr;
  guint8  eimsk;
  guint8  gpio;
  guint8  eecr;

  /* 0x40 */
  guint8  eedr;
  guint16 eear;
  guint8  gtccr;
  guint8  tccr0a;
  guint8  tccr0b;
  guint8  tcnt0;
  guint8  ocr0a;
  guint8  ocr0b;
  guint8  res0x49;
  guint8  gpior1;
  guint8  gpior2;
  guint8  spcr;
  guint8  spsr;
  guint8  spdr;
  guint8  res0x4f;
  guint8  acsr;
  guint8  res0x51;
  guint8  res0x52;
  guint8  smcr;
  guint8  mcusr;
  guint8  mcucr;
  guint8  res0x56;
  guint8  spmcsr;
  guint8  res0x58;
  guint8  res0x59;
  guint8  res0x5a;
  guint8  res0x5b;
  guint8  res0x5c;
  guint16 sp;
  guint8  sreg;

  /* 0x60 */
  guint8  wdtcsr;
  guint8  clkpr;
  guint8  res0x63;
  guint8  res0x64;
  guint8  prr;
  guint8  res0x65;
  guint8  osccal;
  guint8  res0x67;
  guint8  pcicr;
  guint8  eicra;
  guint8  res0x6a;
  guint8  pcmsk0;
  guint8  pcmsk1;
  guint8  pcmsk2;
  guint8  timsk0;
  guint8  timsk1;
  guint8  timsk2;
  guint8  res0x71;
  guint8  res0x72;
  guint8  res0x73;
  guint8  res0x74;
  guint8  res0x75;
  guint8  res0x76;
  guint8  res0x77;
  guint16 adc;
  guint8  adcsra;
  guint8  adcsrb;
  guint8  admux;
  guint8  res0x7d;
  guint8  didr0;
  guint8  didr1;

  /* 0x80 */
  guint8  tccr1a;
  guint8  tccr1b;
  guint8  tccr1c;
  guint8  res0x83;
  guint16 tcnt1;
  guint16 icr1;
  guint16 ocr1a;
  guint16 ocr1b;
  guint8  res0x8c;
  guint8  res0x8d;
  guint8  res0x8e;
  guint8  res0x8f;
  guint8  res0x90;
  guint8  res0x91;
  guint8  res0x92;
  guint8  res0x93;
  guint8  res0x94;
  guint8  res0x95;
  guint8  res0x96;
  guint8  res0x97;
  guint8  res0x98;
  guint8  res0x99;
  guint8  res0x9a;
  guint8  res0x9b;
  guint8  res0x9c;
  guint8  res0x9d;
  guint8  res0x9e;
  guint8  res0x9f;

  /* 0xa0 */
  guint8  res0xa0;
  guint8  res0xa1;
  guint8  res0xa2;
  guint8  res0xa3;
  guint8  res0xa4;
  guint8  res0xa5;
  guint8  res0xa6;
  guint8  res0xa7;
  guint8  res0xa8;
  guint8  res0xa9;
  guint8  res0xaa;
  guint8  res0xab;
  guint8  res0xac;
  guint8  res0xad;
  guint8  res0xae;
  guint8  res0xaf;
  guint8  tccr2a;
  guint8  tccr2b;
  guint8  rcnt2;
  guint8  ocr2a;
  guint8  ocr2b;
  guint8  res0xb5;
  guint8  assr;
  guint8  res0xb7;
  guint8  twbr;
  guint8  twsr;
  guint8  twar;
  guint8  twdr;
  guint8  twcr;
  guint8  twamr;
  guint8  res0xbe;
  guint8  res0xbf;

  /* 0xc0 */
  guint8  ucsr0a;
  guint8  ucsr0b;
  guint8  ucsr0c;
  guint8  res0xc3;
  guint16 ubrr0;
  guint8  udr0;
} AVRControl;

#define avr_control (*(volatile AVRControl *)0)
#define type_check(val,type) (*((&(val) == (type *) 0) ? &(val) : &(val)))
#define avr_low(short)  ((*(guint8 *) &type_check (short, guint16)) + 0)
#define avr_high(short) ((*(guint8 *) &type_check (short, guint16)) + 1)

#define port(bank) (avr_control.port[AVR_PORT##bank])
#define portnum(bank, nr) (P ## bank ## nr)

#define set_bit(v, b) ((v)|=_BV(b))
#define clr_bit(v, b) ((v)&=~_BV(b))
#define get_bit(v, b) (((v)>>(b)) & 1)

#define set_ddr(bank, nr) set_bit (port(bank).ddr, portnum (bank, nr))
#define clr_ddr(bank, nr) clr_bit (port(bank).ddr, portnum (bank, nr))

#define set_port(bank, nr) set_bit (port(bank).port, portnum (bank, nr))
#define clr_port(bank, nr) clr_bit (port(bank).port, portnum (bank, nr))

#define get_pin(bank, nr) get_bit (port(bank).pin, portnum (bank, nr))
