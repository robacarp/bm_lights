//adapted from http://mjijackson.com/2008/02/rgb-to-hsl-and-rgb-to-hsb-color-model-conversion-algorithms-in-javascript

#include "Arduino.h"
#include <math.h>

class Color {

  public:
    int red, green, blue;

    Color() {
      this->red = this->green = this->blue = 100;
    }

    void set_rgb( int red, int green, int blue ){
      int rgb[3] = {
        (int) red,
        (int) green,
        (int) blue
      };

      this->set_rgb(rgb);
    }

    void set_hsb( int hue, int sat, int val) {
      int hsb[3] = { hue, sat, val };
      this->set_hsb(hsb);
    }

    void set_rgb(int* rgb){
      this->red = rgb[0]; this->green = rgb[1]; this->blue = rgb[2];
    }

    void get_rgb(int* rgb){
      rgb[0] = this->red; rgb[1] = this->green; rgb[2] = this->blue;
    }

    void set_hsb(int* hsb){
      int rgb[3] = {0,0,0};
      hsb_to_rgb(hsb,rgb);
      set_rgb(rgb);
    }

    void get_hsb(int* hsb){ 
      int* rgb;
      get_rgb(rgb);
      rgb_to_hsb(rgb,hsb);
    }

    void print_hsb();
    void print_rgb();

    void rgb_to_hsb(int* rgb, int *hsb);
    void hsb_to_rgb(int* hsb, int *rgb);

};

//not vetted
void Color::rgb_to_hsb( int * rgb, int * hsb) {
  /*
  float red, green, blue, min, max, chroma;
  red   = rgb[0] / 255;
  green = rgb[1] / 255;
  blue  = rgb[2] / 255;
  max = max( red, max( green, blue ) );
  min = min( red, min( green, blue ) );
  chroma = max - min;

  //unsigned short hue = 0, sat = 0, val = 0;

  //val = (min + max) / 2;

  if (max == min) {
    hue = sat = 0;
  } else {
    float diff = max - min;
    if (val > 0.5) {
      sat = diff / ( 2 - max - min );
    } else {
      sat = diff / ( max + min );
    }

    if (abs(max - red) < 0.01) {
      hue = ( green - blue ) / diff + ( green < blue ? 6 : 0 );
    } else if (abs(max - green) < 0.01) {
      hue = ( blue - red ) / diff + 2;
    } else if (abs(max - blue) < 0.01) {
      hue = ( red - green ) / diff + 4;
    }
  }

  //hsb[0] = hue;
  //hsb[1] = sat;
  //hsb[2] = val;
  // */
}


/* hue => [0,360], sat => [0,100], val => [0,100] */
void Color::hsb_to_rgb( int * hsb, int * rgb) {
  float r, g, b;
  float sat = (float)hsb[1] / 100;
  float bri = (float)hsb[2] / 100;
  float hue = hsb[0] / 60.0;
  float chroma = bri * sat;
  float x;
  x = chroma * (1 - abs( (fmod(hue, 2.0) - 1)));

       if (hue >= 0 && hue < 1) { r = chroma; g =  x; b = 0; }
  else if (hue >= 1 && hue < 2) { r = x; g =  chroma; b = 0; }
  else if (hue >= 2 && hue < 3) { r = 0; g =  chroma; b = x; }
  else if (hue >= 3 && hue < 4) { r = 0; g =  x; b = chroma; }
  else if (hue >= 4 && hue < 5) { r = x; g =  0; b = chroma; }
  else if (hue >= 5 && hue < 6) { r = chroma; g =  0; b = x; }
     else { rgb[0] = 0; rgb[1] = 0; rgb[2] = 0; }

  x = bri - chroma;
  r += x;
  g += x;
  b += x;

  rgb[0] = r * 255;
  rgb[1] = g * 255;
  rgb[2] = b * 255;
}


#ifdef DEBUG
void Color::print_rgb(){
  Serial.print("red: ");
  Serial.print( red );
  Serial.print(" green: ");
  Serial.print( green );
  Serial.print(" blue: ");
  Serial.println( blue );
}

void Color::print_hsb(){
  int hsb[3];
  int rgb[3] = { red, green, blue };

  rgb_to_hsb(rgb,hsb);

  Serial.print("hue: ");
  Serial.print(hsb[0]);
  Serial.print(" sat: ");
  Serial.print(hsb[1]);
  Serial.print(" val: ");
  Serial.println(hsb[2]);
}
#endif
