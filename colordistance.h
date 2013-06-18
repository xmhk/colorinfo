#ifndef COLORDISTANCE_H
#define COLORDISTANCE_H

#include "structdefs.h"
#include <math.h>

#include "colordefinitions.h"
#include "rgbconversion.h"

int rgb_get_nearest_color( struct RGB_Double *rgbd,  struct ColorInfo color_data[COLOR_NAMES_MAX] );

#endif
