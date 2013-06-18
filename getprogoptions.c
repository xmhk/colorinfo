
#include "errors.h"
#include "structdefs.h"

#include <getopt.h>
#include "getprogoptions.h"

void get_program_options( int argc, char **argv , struct program_options *options)
{
 
  int c;
  while (1)
    {
      static struct option long_options[] =
	{
	  {"help", no_argument,     0, 'h'},
	  {"rgb",  no_argument,     0, 'r'},
	  {"RGB",  no_argument,     0, 'R'},
	  {"hsv",  no_argument,     0, 's'},
	  {"usage", no_argument,    0, 'u'},
	  {"verbose", no_argument,  0, 'v'},              
	  {"hex",     no_argument,  0, 'x'},
	  {0, 0, 0, 0}
	};

      int option_index = 0;
      c = getopt_long (argc, argv, "hrRsuvx",
		       long_options, &option_index);
      if (c == -1)
	break;     
      switch (c)
	{
	case 'h':
	  options->help=1;
	  options->switchnum = options->switchnum +1;
	  break;
	case 'r':
	  options->rgb1=1;
	  options->switchnum = options->switchnum + 1;
	  break;
	case 'R':
	  options->rgb2=1;
	  options->switchnum = options->switchnum + 1;
	  break;
	case 's':
	  options->hsv = 1;
	  options->switchnum = options->switchnum + 1;	       
	  break;
	case 'u':
	  options->help = 1;
	  break;
	case 'v':
	  options->verbose=1;
	  break;     
	case 'x':
	  options->hex = 1;
	  options->switchnum = options->switchnum + 1;
	  break;
	default:
	  options->errorcode = INVALID_OPTIONS_GIVEN;
	  break;
	}
    }
}

