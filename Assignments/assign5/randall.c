/* Generate N bytes of random output.  */

/* When generating output this program uses the x86-64 RDRAND
   instruction if available to generate random numbers, falling back
   on /dev/random and stdio otherwise.

   This program is not portable.  Compile it with gcc -mrdrnd for a
   x86-64 machine.

   Copyright 2015, 2017, 2020 Paul Eggert

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include <errno.h>
#include <immintrin.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <ctype.h>

#include "output.h"
#include "rand64-hw.h"
#include "rand64-sw.h"
#include "checkCPU.h"
#include "options.h"

/* Main program, which outputs N bytes of random data.  */

int randomizeVals(int input_option, int output_mode, char* dev_file_name, int num_char_per_line, int nbytes)
{
  #if 0
  /* Check arguments.  */
  bool valid = false;
  long long nbytes;
  if (argc == 2)
    {
      char *endptr;
      errno = 0;
      nbytes = strtoll (argv[1], &endptr, 10);
      if (errno)
	perror (argv[1]);
      else
	valid = !*endptr && 0 <= nbytes;
    }
  if (!valid)
    {
      fprintf (stderr, "%s: usage: %s NBYTES\n", argv[0], argv[0]);
      return 1;
    }

  /* If there's no work to do, don't worry about which library to use.  */
  if (nbytes == 0)
    return 0;

  /* Now that we know we have work to do, arrange to use the
     appropriate library.  */
  
  #endif
  void (*initialize) (void);
  // printf("inside %s , %d\n\r", __func__, __LINE__);
  unsigned long long (*rand64) (void);
  void (*finalize) (void);
  
  if(input_option == RDRAND)  //hardware option
  {
    // printf("going into rdrand condition");
    if (rdrand_supported ())
    {
      // printf("hardware option supported");
      initialize = hardware_rand64_init;
      initialize();
      rand64 = hardware_rand64;
      finalize = hardware_rand64_fini;
    }
    else{
      fprintf (stderr, "Invalid argument!"); 
      return 1;
    }
  }
  else if (input_option == MRAND48_R) //software option
  {
    initialize = mrand48_r_init;
    initialize();
    rand64 = software_mrand48_r;
    finalize = mrand48_r_fini;

  }
  else if(input_option == DEV_RAND)
  {
    software_rand64_file_init(dev_file_name);
    rand64 = software_rand64;
    finalize = software_rand64_fini;
  }
 

  // initialize ();
  int wordsize = sizeof rand64 ();
  int output_errno = 0;
 
 if(output_mode == STDIO)
 {
    do 
      {
        unsigned long long x = rand64();
        int outbytes = nbytes < wordsize ? nbytes : wordsize;
        if (!writebytes (x, outbytes))
        {
          output_errno = errno;
          break;
        }
          nbytes -= outbytes;
      }
    while (0 < nbytes);
 }
 else {
   
    unsigned long long *randBuf;
    int numRand = num_char_per_line / wordsize + (num_char_per_line % wordsize > 0);
    randBuf = malloc(numRand * wordsize);

    if (!randBuf) {
      return 1;
    } 

    do {
      for (int i = 0; i < numRand; i++) {
        randBuf[i] = rand64();
      }
      ssize_t outbytes = num_char_per_line < nbytes ? num_char_per_line : nbytes;
      outbytes = writeLineByLine(randBuf, outbytes);

      if (outbytes == -1)
          break;

        nbytes -= outbytes;
      }
    while (0 < nbytes);

      free(randBuf);
  }

  if (fclose (stdout) != 0)
    output_errno = errno;

  if (output_errno)
    {
      errno = output_errno;
      perror ("output");
    }

  finalize ();
  return !!output_errno;

}

int
main (int argc, char **argv)
{
  int nbytes = 0;
  int ret, num_char_per_line;
  int input_option = RDRAND; 
  int output_mode = STDIO;
  char dev_file_name[256];
  // printf("get opt successfully retrieved options: \n\r");
  memset(dev_file_name, 0x00, 256);
  ret = get_options(argc, argv, &input_option, &output_mode, dev_file_name, &num_char_per_line, &nbytes);
  if (ret == 0)
  {
    // printf("################################### \n\r input option is %d , output mode is %d , file name is %s , num char per line is %d , nbytes is %lld \n\r", input_option, output_mode, dev_file_name, num_char_per_line, nbytes);
    ret = randomizeVals(input_option, output_mode, dev_file_name, num_char_per_line, nbytes);
  }
  else
    exit(1);

  
}
  
  
