colorinfo
=========

a small CL tool to convert given color values (RGB, HEX,HSV) into color names ("red","blue").
I wrote this for myself as i am partly colorblind. Maybe it is useful to someone else.

Part of the code is based / directly derived on the work of codebrainz (https://github.com/codebrainz/color-names),
which was very useful to me. Thanks for that.

License is GPL2 /  Creative Commons Attribution-ShareAlike License (for the Wikipedia Article http://en.wikipedia.org/wiki/List_of_colors);  

usage
=========
 usage: colorinfo [OPTARG] [MODE] [C1] [C2] [C3]
 
 OPTARGs:
         -h  --help        print this message
         -v  --verbose     verbose output

 MODEs:
         -x  --hex S       hex input. (S as Hex-String)
         -s  --hsv H S V   hsv input. (H real 0...360. S,V real 0..1)
         -r  --rgb R G B   rgb input. (R..G integers 0...255)
         -R  --RGB R G B   rgb input. (R..G real number 0...1)


* HEX-Mode: a string with 6 characters, ranging from 0..9 and A..F
  example: colorinfo -x AA00CC
  	   colorinfo --hex --verbose BBBB77

* rgb 1 Mode: three RGB values as integers, ranging from 0 to 255 separated by spaces
  example: colorinfo -r 22 33 255
           colorinfo --rgb --verbose 00 12 255 

* rgb2 Mode: the RGB values are given as real numbers between 0 and one
  example: colorinfo -R 0.2 0.3 0.5
           colorinfo --RGB --verbose 0.0 1.0 0.5

* HSV Mode: three real numbers. Hue given as angle (0..360), Saturation and Value as real numbers (0..1)
  example: colorinfo -s 200 0.1 0.9
  	   colorinfo --hsv 355 0.5 0.6



source files
=========

short overview of the source files:

-build.sh ............... a build script, assuming that you use gcc.
-cnames2.c .............. the main program
-colordefinitions.c/.h .. color "database"
-colordistance.c/.h ..... calculate the distance of two points in RGB space
-errors.h ............... define some error codes
-getoptions.c/.h ........ handle command line options
-messages.c/.h .......... various output functions
-rgbconversion.c/.h ..... functions to parse and convert different color inputs
-structdefs.h ........... structure definitions

