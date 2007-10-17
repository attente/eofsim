#include <termios.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#include "conversion.h"
#include "physics.h"
#include "serial.h"

int
serial_open (void)
{
  struct termios term;
  int fd;

  fd = open ("/dev/ttyUSB0", O_RDWR);

  if (fd < 0)
  {
    perror ("can't open /dev/ttyUSB0");
    exit (1);
  }

  if (tcgetattr (fd, &term))
  {
    perror ("tcgetattr ('/dev/ttyUSB0')");
    exit (1);
  }

  term.c_iflag = IGNPAR;
  term.c_oflag = 0;
  term.c_lflag = 0;
  term.c_cflag = CLOCAL | CS8 | CREAD;
  term.c_cc[VMIN] = 0;
  term.c_cc[VTIME] = 0;
  cfsetospeed (&term, B9600);

  if (tcsetattr (fd, 0, &term))
  {
    perror ("tcsetattr ('/dev/ttyUSB0')");
    exit (1);
  }

  return fd;
}

static void
serial_shift (char *buffer, int *length, int shift)
{
  *length -= shift;
  memmove (buffer, &buffer[shift], *length);
}

static void
serial_packet (char pkt[3])
{
  printf ("%d\t%d\t%d\n", pkt[0]-'m', pkt[1]-'m', pkt[2]-'m');
  physics_set_thrust (pkt[0] - 'm');
  physics_set_flaps (pkt[1] - 'm');
  physics_update ();
}

bool
serial_read (int fd)
{
  static char buffer[200];
  static int length;
  int len;

  len = read (fd, &buffer[length], sizeof buffer - length);

  if (len <= 0)
    return false;

  length += len;

  while (length >= 4)
    if (buffer[3] == '\n')
    {
      serial_packet (buffer);
      serial_shift (buffer, &length, 3);
    }
    else
      serial_shift (buffer, &length, 1);

  return true;
}

void
serial_write (int fd,
              int a,
              int b,
              int c)
{
  unsigned char byte;

  if (a < 0) a = 0;
  if (b < 0) b = 0;
  if (c < 0) c = 0;
  if (b > 1023) b = 1023;
  if (b > 1023) b = 1023;
  if (c > 1023) c = 1023;

  byte = '*';
  write (fd, &byte, sizeof byte);

  byte = analog_to_digital[a];
  write (fd, &byte, sizeof byte);

  byte = analog_to_digital[b];
  write (fd, &byte, sizeof byte);

  byte = analog_to_digital[c];
  write (fd, &byte, sizeof byte);
}
