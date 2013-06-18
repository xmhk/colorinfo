#ifndef STRUCTDEFS_H
#define STRUCTDEFS_H



struct program_options{
  int errorcode;
  int hex;
  int hsv;
  int help;
  int optind;
  int rgb1;
  int rgb2;
  int switchnum;
  int verbose;
};



typedef struct ColorInfo {
  const char *name;
  const char *hex;
  struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
  } rgb;
} ColorInfo;



struct hexstring{
  char hex[7];
};


struct RGB_Double{
  double r;
  double g;
  double b;
};


struct RGB_Int{
  int r;
  int g;
  int b;
};



struct HSV_Double{
  double h;
  double s;
  double v;
};


#endif
