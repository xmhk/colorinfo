
#ifndef RGBCONVERSION_H
#define RGBCONVERSION_H

#include "structdefs.h"
#include <math.h>
#include <stdio.h>
#include <string.h>



int are_strings_valid_rgb1_input(char *rarg,char *garg,char *barg,struct RGB_Int *rgb);

int are_strings_valid_rgb2_input(char *rarg,char *garg,char *barg,struct RGB_Double *rgb);

int are_strings_valid_hsv_input( char *Harg, char *Sarg, char *Varg, struct HSV_Double *hsv);

int is_valid_hexstring( char *hexstring );



char number2hex(int number);
int hexchar2int(char inputchar);
void hex2rgbint( char *hexstring, struct RGB_Int *rgb);
void rgbInt2hex( struct RGB_Int *rgb, struct hexstring *hex  );


void rgbDouble2rgbInt( struct RGB_Double *rgbD, struct RGB_Int *rgbI);

void rgbInt2rgbDouble( struct RGB_Int *rgbI, struct RGB_Double *rgbD);


void hsvDouble2rgbDouble(struct HSV_Double* hsv, struct RGB_Double* rgb);

void rgbDouble2hsvDouble( struct RGB_Double *rgb, struct HSV_Double *hsv);


#endif
