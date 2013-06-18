

#include "colordistance.h"
#include "structdefs.h"
#include <math.h>

#include "colordefinitions.h"
#include "rgbconversion.h"


// ************************************************
//
// calculate the difference of two triplets in the 
// RGB colorspace and return the color index with
// the smallest one
//

int rgb_get_nearest_color( struct RGB_Double *rgbd,  struct ColorInfo color_data[COLOR_NAMES_MAX] ){
  // return the index of the best fit in color_data for r,g,b
  int  i, bestindex;
  struct RGB_Double actrgbd;
  struct RGB_Int actrgbi;
  double olderror, newerror;
  bestindex = 0;
  olderror = 3.0; // this is the maximum distance in RGB space squared
  for (i=0;i < COLOR_NAMES_MAX; i++){
    actrgbi.r = color_data[i].rgb.r; //create tmp rgbInt instance
    actrgbi.g = color_data[i].rgb.g;
    actrgbi.b = color_data[i].rgb.b;
    rgbInt2rgbDouble( &actrgbi, &actrgbd ); //convert to Double instance
    newerror =  sqrt(
		     (actrgbd.r-rgbd->r) *  (actrgbd.r-rgbd->r) 
		     +(actrgbd.g-rgbd->g) *  (actrgbd.g-rgbd->g) 
		     +(actrgbd.b-rgbd->b) *  (actrgbd.b-rgbd->b) 
		     );
    if (newerror < olderror) {
      olderror = newerror;
      bestindex = i;
    }
  }
  return bestindex;
}

