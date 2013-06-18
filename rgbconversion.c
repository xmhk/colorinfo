#include <math.h>
#include <stdio.h>
#include <string.h>
#include "structdefs.h"
#include "rgbconversion.h"







int are_strings_valid_rgb1_input(char *rarg,char *garg,char *barg,struct RGB_Int *rgb){
  int error = 1;
  sscanf(rarg, "%d", &rgb->r);
  sscanf(garg, "%d", &rgb->g);
  sscanf(barg, "%d", &rgb->b);
  if (  (rgb->r <0) || (rgb->r >255) || 
        (rgb->g <0) || (rgb->g >255) ||
	(rgb->b <0) ||(rgb->b >255)){
    error = 0;
  }
  return error;
}



int are_strings_valid_rgb2_input(char *rarg,char *garg,char *barg,struct RGB_Double *rgb){
  int error = 1;
  sscanf(rarg, "%lf", &rgb->r);
  sscanf(garg, "%lf", &rgb->g);
  sscanf(barg, "%lf", &rgb->b);
  if (  (rgb->r <0) || (rgb->r >1.0) || 
        (rgb->g <0) || (rgb->g >1.0) ||
	(rgb->b <0) ||(rgb->b >1.0)){
    error = 0;
  }
  return error;
}




int are_strings_valid_hsv_input( char *Harg, char *Sarg, char *Varg, struct HSV_Double *hsv){
  int error = 1;
  sscanf(Harg, "%lf", &hsv->h);
  sscanf(Sarg, "%lf", &hsv->s);
  sscanf(Varg, "%lf", &hsv->v);
  if (  (hsv->h <0.0) || (hsv->h >360.0) || 
        (hsv->s <0.0) || (hsv->s >1.0) ||
	(hsv->v <0.0) ||(hsv->v >1.0)){
    error = 0;
  }
  return error;
}


int is_valid_hexstring( char *hexstring )
{

  //  printf("\n input : %s", hexstring);
  //int result = 1;
  int i;
  // check valid length
  if (! ( (strlen(hexstring)==6) || (strlen(hexstring)==7))   ){ return 0;}

  if (strlen(hexstring)==7){
    char neustring[6];
    for (i=0;i<6;i++){
      neustring[i] = hexstring[i+1];
    }
    hexstring = neustring;    
  }

  for (i=0; i<6;i++) {   //check whether there are invalid characters
    if (  !(
	    ((hexstring[i]>=48)&&(hexstring[i]<=57)) // 0..9
	     ||((hexstring[i]>=97)&&(hexstring[i]<=102)) //a..f
	     ||((hexstring[i]>=65)&&(hexstring[i]<=70)) //A..F
	     ))
      {
	return 0;
      }}
	
  return 1;

  
}

// **************************************************
//
// conversions
//




char number2hex(int number){
    char c;
  switch(number){

  case 0: c= '0';break;
  case 1: c= '1';break;
  case 2: c= '2';break;
  case 3: c= '3';break;
  case 4: c= '4';break;
  case 5: c= '5';break;
  case 6: c= '6';break;
  case 7: c= '7';break;
  case 8: c= '0';break;
  case 9: c= '0';break;
  case 10: c= 'A';break;
  case 11: c= 'B';break;
  case 12: c= 'C';break;
  case 13: c= 'D';break;
  case 14: c= 'E';break;
  case 15: c= 'F';break;

  }
  return c;
}




int hexchar2int(char inputchar){
  switch (inputchar){
  case '0': return 0; break;
  case '1': return 1; break;
  case '2': return 2; break;
  case '3': return 3; break;
  case '4': return 4; break;
  case '5': return 5; break;
  case '6': return 6; break;
  case '7': return 7; break;
  case '8': return 8; break;
  case '9': return 9; break;
  case 'a': return 10;break;
  case 'A': return 10;break;
  case 'b': return 11;break;
  case 'B': return 11;break;
  case 'c': return 12;break;
  case 'C': return 12;break;
  case 'd': return 13;break;
  case 'D': return 13;break;
  case 'e': return 14;break;
  case 'E': return 14;break;
  case 'f': return 15;break;
  case 'F': return 15;break;
  default: return -1;break;    
  }
}




void hex2rgbint( char *hexstring, struct RGB_Int *rgb)
{
  int i;
  int cvalues[6];
  if (strlen(hexstring)==7){
    char neustring[6];
    for (i=0;i<6;i++){
      neustring[i] = hexstring[i+1];
    }
    hexstring = neustring;    
  }

  for (i=0;i<6;i++){
    cvalues[i] = hexchar2int(hexstring[i]);
  }
  rgb->r = cvalues[0] * 16 + cvalues[1];
  rgb->g = cvalues[2] * 16 + cvalues[3];
  rgb->b = cvalues[4] * 16 + cvalues[5];	
}





  void rgbInt2hex( struct RGB_Int *rgb, struct hexstring *hex  )
{
  hex->hex[0]='#';
  hex->hex[1] = number2hex( rgb->r/16);
  hex->hex[2] = number2hex( rgb->r%16);
  hex->hex[3] = number2hex( rgb->g/16);
  hex->hex[4] = number2hex( rgb->g%16);
  hex->hex[5] = number2hex( rgb->b/16);
  hex->hex[6] = number2hex( rgb->b%16);
  
}




void rgbDouble2hsvDouble( struct RGB_Double *rgb, struct HSV_Double *hsv)
{
  double rgbmax = rgb->r;
  double rgbmin = rgb->r;

  if (rgb->g > rgbmax) { rgbmax = rgb-> g;}
  if (rgb->b > rgbmax) { rgbmax = rgb-> b;}
  
  if (rgb->g < rgbmin) {rgbmin = rgb-> g;}
  if (rgb->b < rgbmin) {rgbmin = rgb-> b;}
  // H
  if (rgbmax == rgbmin) {
    hsv->h =0.0;
  } else {
    if (rgbmax == rgb->r) {  hsv->h = 60 *  ( rgb->g - rgb->b) / (rgbmax - rgbmin);}
    if (rgbmax == rgb->g) {  hsv->h =   60 *( 2.0 + ( rgb->b - rgb->r) / (rgbmax - rgbmin));}
    if (rgbmax == rgb->b) {  hsv->h =  60 * (4.0 +  ( rgb->r - rgb->g) / (rgbmax - rgbmin));}
  }
  if (hsv->h < 0 ){ hsv->h = hsv->h + 360; }
  // S
  if (rgbmax == 0.0) {
    hsv->s = 0;
  }
  else {
    hsv->s = (rgbmax - rgbmin ) / rgbmax;
  }
  // V
  hsv->v = rgbmax;
  //  printf("\n rgbmax %.3f  rgbmin %.3f  \n",rgbmax,rgbmin);
}


void rgbDouble2rgbInt( struct RGB_Double *rgbD, struct RGB_Int *rgbI)
{
  rgbI->r= (int) round( rgbD->r * 255);
  rgbI->g= (int) round( rgbD->g * 255);
  rgbI->b= (int) round( rgbD->b * 255);
}


void rgbInt2rgbDouble( struct RGB_Int *rgbI, struct RGB_Double *rgbD){
  rgbD->r = (double) rgbI->r/255.0;
  rgbD->g = (double) rgbI->g/255.0;
  rgbD->b = (double) rgbI->b/255.0;
}



void hsvDouble2rgbDouble(struct HSV_Double* hsv, struct RGB_Double* rgb){
  double hi,f,p,q,t;
  double h = hsv->h;
  double s = hsv->s;
  double v = hsv->v;

  hi = floor(h/60.0 );

  f = (h/60.0 - hi);
  p = v * (1-s);
  q = v * (1-s*f);
  t = v * (1-s*(1-f));
  switch ( (int)hi){
  case 0:
    rgb->r = v;
    rgb->g = t;
    rgb->b = p;
    break;
  case 6:
    rgb->r = v;
    rgb->g = t;
    rgb->b = p;
    break;    
  case 1:
    rgb->r = q;
    rgb->g = v;
    rgb->b = p;
    break;
  case 2:
    rgb->r = p;
    rgb->g = v;
    rgb->b = t;
    break;
  case 3:
    rgb->r = p;
    rgb->g = q;
    rgb->b = v;
    break;
  case 4:
    rgb->r = t;
    rgb->g = p;
    rgb->b = v;
    break;
  case 5:
    rgb->r = v;
    rgb->g = p;
    rgb->b = q;
    break;
  }
}



