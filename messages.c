#include <stdio.h>
#include "messages.h"

#include "colordefinitions.h"
#include "rgbconversion.h"


const char PROGNAME[23] = "colorinfo";


void print_usage(){

  printf("\n usage: %s [OPTARG] [MODE] [C1] [C2] [C3]",PROGNAME);
  printf("\n ");
  printf("\n OPTARGs:");
  printf("\n         -h  --help        print this message");
  printf("\n         -v  --verbose     verbose output");
  printf("\n\n MODEs:");
  printf("\n         -x  --hex S       hex input. (S as Hex-String");
  printf("\n         -s  --hsv H S V   hsv input. (H real 0...360. S,V real 0..1)");
  printf("\n         -r  --rgb R G B   rgb input. (R..G integers 0...255)");
  printf("\n         -R  --RGB R G B   rgb input. (R..G real number 0...1)");
  printf("\n");
}

void print_error_message( int errorcode ){
  switch( errorcode)
    {
    case 1:
      printf("\nError: invalid options given. %s --help for usage", PROGNAME);
      break;
    case 11:
      printf("\nError: hex mode but no argument given. A valid example is :  %s --hex 00AAFF",PROGNAME);
      break;
    
    case 12:
      printf("\nError: hex mode but invalid argument given. A valid example is :  %s --hex 00AAFF",PROGNAME);
      break;
    case 21:
      printf("\nError: hsv mode but invalid number of arguments given. A valid example is :  %s --hsv 200 0.5 0.5",PROGNAME);
      break;
    case 22:
      printf("\nError: hsv mode but invalid arguments given. A valid example is :  %s --hsv 200 0.5 0.5",PROGNAME);
      break;

    case 31:
      printf("\nError: rgb1 mode but invalid number of arguments given. A valid example is :  %s --rgb 0 255 125",PROGNAME);
      break;
    case 32:
      printf("\nError: rgb1 mode but invalid arguments given. A valid example is :  %s --rgb 0 255 125",PROGNAME);
      break;


    case 41:
      printf("\nError: rgb2 mode but invalid number of arguments given. A valid example is :  %s --RGB 1.0 0.0 0.42",PROGNAME);
      break;
    case 42:
      printf("\nError: rgb2 mode but invalid arguments given. A valid example is :  %s --RGB 1.0 0.0 0.42",PROGNAME);
      break;

    };
};



void print_result( int bestindex ,  struct ColorInfo color_data[COLOR_NAMES_MAX]) {
  printf("%s\n",color_data[bestindex].name);  
}



void print_result_verbose(  int bestindex ,  
			    struct ColorInfo color_data[COLOR_NAMES_MAX],
			    int argc, 
			    char **argv,
			    struct RGB_Double *rgbd,
			    int mode)  
{
  int i;
  //  char *hexout;
  struct hexstring hex;
  struct RGB_Int rgbint;
  struct RGB_Int rgbintresult;
  struct RGB_Double rgbdresult;
  struct HSV_Double hsvresult, hsv;

  //convert
  rgbintresult.r = color_data[bestindex].rgb.r;
  rgbintresult.g = color_data[bestindex].rgb.g;
  rgbintresult.b = color_data[bestindex].rgb.b;
  rgbDouble2rgbInt( rgbd, &rgbint);
  rgbInt2rgbDouble( &rgbintresult, &rgbdresult);
  rgbDouble2hsvDouble( rgbd, &hsv);
  rgbDouble2hsvDouble( &rgbdresult, &hsvresult);

  rgbInt2hex( &rgbint, &hex);

  printf("\n call:  ");
  for (i=0;i<argc;i++)
    {
      printf("%s ",argv[i]);
    }
  printf("\n detected mode: ");
  switch(mode){
  case  1: printf("HEX");break;
  case  2: printf("HSV");break;
  case  3: printf("RGB 1 ");break;
  case  4: printf("RGB 2");break;
  }

  
  printf("\n        |  input color          |  nearest result");
  printf("\n-------------------------------------------------");
  printf("\n HEX    |       %s            |      %s",hex.hex, color_data[bestindex].hex);
  printf("\n HSV    | %3.1f %.4f %.4f    | %3.1f %.4f %.4f ",hsv.h,hsv.s,hsv.v,hsvresult.h, hsvresult.s,hsvresult.v);
  printf("\n RGB(1) | %6d %6d %6d  | %6d %6d %6d", rgbint.r, rgbint.g, rgbint.b, rgbintresult.r,  rgbintresult.g,  rgbintresult.b);
  printf("\n RGB(2) | %.4f %.4f %.4f  | %.4f %.4f %.4f", rgbd->r, rgbd->g, rgbd->b, rgbdresult.r, rgbdresult.g,rgbdresult.b);
  printf("\n        |                       |");
  printf("\n name   |                       |  %s\n\n",color_data[bestindex].name);  

}
