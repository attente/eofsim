#include "serial.h"

int
main (void)
{
  int fd;
  
  fd = serial_open ();

  while (serial_read (fd))
  {
  }

  return 0;
}
