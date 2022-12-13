#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "rand64-sw.h"

/* Software implementation.  */

/* Input stream containing random bytes.  */
static FILE *urandstream;

/* Initialize the software rand64 implementation.  */
void
software_rand64_init (void)
{
  urandstream = fopen ("/dev/random", "r");
  if (! urandstream)
    abort ();
}

void software_rand64_file_init (char * s) //for any inputted file name
{
  urandstream = fopen (s, "r");
  if (! urandstream)
    abort ();
}

/* Return a random value, using software operations.  */
unsigned long long
software_rand64 (void)
{
  unsigned long long int x;
  if (fread (&x, sizeof x, 1, urandstream) != 1)
    abort ();
  return x;
}

/* Finalize the software rand64 implementation.  */
void
software_rand64_fini (void)
{
  fclose (urandstream);
}

void mrand48_r_init (char *filename) {
}

long int software_mrand48_r (void) {
  struct drand48_data tmp;
  long int result;

  srand48_r(time(NULL), &tmp);
  mrand48_r(&tmp, &result);
  // printf("mrand48_r result: %d\n",result);
  return result;
}

void mrand48_r_fini (void) {
}