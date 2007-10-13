#include "runtime.h"

void
one_iteration (void)
{
  static signed char count[3];
  static char iter;

  if (((++iter) & 7) == 0)
  {
    int i;
    
    for (i = 0; i < 3; i++)
    {
      send_byte (count[i] + 'm');
      count[i] = 0;
    }

    send_byte ('\n');
  }

  if (get_pin (D, 7))
  {
    if (count[0] < 0)
      count[0] = 0;
    count[0]++;
  }

  if (get_pin (B, 0))
  {
    if (count[0] > 0)
      count[0] = 0;
    count[0]--;
  }

  if (get_pin (B, 1))
  {
    if (count[1] < 0)
      count[1] = 0;
    count[1]++;
  }

  if (get_pin (B, 2))
  {
    if (count[1] > 0)
      count[1] = 0;
    count[1]--;
  }

  if (get_pin (B, 3))
  {
    if (count[2] < 0)
      count[2] = 0;
    count[2]++;
  }

  if (get_pin (B, 4))
  {
    if (count[2] > 0)
      count[2] = 0;
    count[2]--;
  }
}
