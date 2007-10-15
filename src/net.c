#include <arpa/inet.h>
#include <unistd.h>
#include "net.h"

int
net_open (void)
{
  return socket (PF_INET, SOCK_DGRAM, 0);
}

int
net_bind (void)
{
  net_addr addr;
  int fd;

  fd = net_open ();
  net_addr_set (&addr, NULL);
  if (bind (fd, (struct sockaddr *) &addr, sizeof addr))
  {
    close (fd);
    return -1;
  }

  return fd;
}

bool
net_addr_set (net_addr   *addr,
              const char *ip)
{
  addr->sin_family = AF_INET;
  addr->sin_port = htons (9778);
  addr->sin_addr.s_addr = 0;
  if (ip)
  {
    if (!inet_aton (ip, &addr->sin_addr))
      return false;
  }

  return true;
}
