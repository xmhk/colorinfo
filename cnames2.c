#include <stdio.h>
#include <math.h>
#include <getopt.h>
#include <string.h>


#include "colordefinitions.h" //list of colors
#include "colordistance.h"    //calc rgb distance
#include "errors.h"           //error codes
#include "getprogoptions.h"   //option parsing
#include "messages.h"         //print messages
#include "rgbconversion.h"    //handle rgb input
#include "structdefs.h"       //define structures 

// ************************************************
//
// Main program - switching between options
//

     
int  main (int argc, char **argv)
{

  struct program_options options={0,0,0,
				  0,0,0,
				  0,0,0};
 
  int bestindex;

  struct RGB_Double rgbdouble;
  struct RGB_Int rgbint;
  struct HSV_Double hsvdouble;
  struct ColorInfo color_data[COLOR_NAMES_MAX];
  
  // initiate the reference colors
  get_color_definitions(color_data);
  
  // get program options from argv parsing
  get_program_options(argc,argv,&options);

  //no mode given
  if ((options.switchnum==0) ||(options.switchnum<1) ){ options.errorcode = INVALID_OPTIONS_GIVEN; }
  //if more than one mode is given
  if (options.switchnum>1){printf("\n can not operate more than one modes simultanously\n");}
  
  //exactly one mode given
  if (options.switchnum==1){
    //==================================================
    // RGB with 0..255 input
    //
    if (options.rgb1){
      //      printf("\n RGB1 mode");
      //printf("\n optind = %d  argc = %d\n",optind,argc);
      if ( argc - optind >2 ){
	if (are_strings_valid_rgb1_input(argv[optind],
					 argv[optind+1],
					 argv[optind+2],
					 &rgbint)){
	  rgbInt2rgbDouble( &rgbint, &rgbdouble);
	}
	else{
	  options.errorcode = RGB1_WRONG_ARGUMENTS;
	}
      }
      else
	{options.errorcode = RGB1_WRONG_NUMBER_OF_ARGS;
	}


    }
    //==================================================
    // RGB with 0.. 1 input
    //
    if (options.rgb2){      
      if ( argc - optind >2 ){
	if (are_strings_valid_rgb2_input(argv[optind],
					 argv[optind+1],
					 argv[optind+2],
					 &rgbdouble)){
	  rgbDouble2rgbInt( &rgbdouble, &rgbint);
	  //	  rgbInt2rgbDouble( &rgbint, &rgbdouble);
	}
	else{
	  options.errorcode = RGB2_WRONG_ARGUMENTS;
	}
      }
      else
	{options.errorcode = RGB2_WRONG_NUMBER_OF_ARGS;
	}

    }
    //==================================================
    // RGB hex - input
    //
    if (options.hex==1){
      if (optind <argc){
	if (is_valid_hexstring(argv[optind]))
	  {
	    hex2rgbint( argv[optind],&rgbint);
	    rgbInt2rgbDouble( &rgbint, &rgbdouble);
	  }
	
	else
	  {options.errorcode=HEX_INVALID_ARG;}
      }
      else { // no Hexstring argumnent given
	options.errorcode = HEX_NO_ARG;
      }
    }
    //==================================================
    // HSV input
    //
    if (options.hsv==1){
      if ( argc - optind >2 ){
	if (are_strings_valid_hsv_input(argv[optind],
					argv[optind+1],
					argv[optind+2],
					&hsvdouble))
	  {
	    hsvDouble2rgbDouble( &hsvdouble, &rgbdouble);
	    rgbDouble2rgbInt( &rgbdouble, &rgbint);
	  }
	else{
	  options.errorcode = HSV_WRONG_ARGUMENTS;
	}
      }
      else
	{options.errorcode = HSV_WRONG_NUMBER_OF_ARGS;
	}
    }   
  }   // end exactly one argument was given
  
 
  if (options.errorcode==0){ //succesful parsing, now calculate and print result or print help
 
    if (options.help==1){
      print_usage();
    }
    else {
      bestindex = rgb_get_nearest_color( &rgbdouble,color_data);
      if (options.verbose==0){
	print_result( bestindex, color_data);
      }
      else {print_result_verbose( bestindex, 
				  color_data,
				  argc,
				  argv,
				  &rgbdouble,
				  1*options.hex + 2 * options.hsv + 3 * options.rgb1 + 4*options.rgb2);
      } // end verbose output
    } // end succesfull parsing + output
  } // end options.errorcode = 1
  else // some error occured 
    { 
      print_error_message(options.errorcode);
      printf("\n");
    }
  return 0;
}


