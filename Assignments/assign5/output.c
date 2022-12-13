#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "output.h"

bool writebytes (unsigned long long x, int nbytes)
{
  do
    {
      if (putchar (x) < 0)
	return false;
      x >>= CHAR_BIT;
      nbytes--;
    }
  while (0 < nbytes);

  return true;
}

ssize_t writeLineByLine(unsigned long long buf, ssize_t outbytes) {
  ssize_t ret;
  ret = write(1, buf, outbytes);
  return ret;
}