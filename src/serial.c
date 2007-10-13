#include <termios.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

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
  printf ("got %c %c %c\n", pkt[0], pkt[1], pkt[2]);
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
