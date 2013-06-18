#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdio.h>
#include "colordefinitions.h"
#include "rgbconversion.h"

void print_usage();

void print_error_message( int errorcode );

void print_result( int bestindex, struct ColorInfo color_data[COLOR_NAMES_MAX] );

void print_result_verbose( int bestindex ,  
			   struct ColorInfo color_data[COLOR_NAMES_MAX],
			   int argc, 
			   char **argv,
			   struct RGB_Double *rgbd,
			   int mode);

#endif
