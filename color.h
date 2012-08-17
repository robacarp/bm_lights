  //nicked from http://mjijackson.com/2008/02/rgb-to-hsl-and-rgb-to-hsv-color-model-conversion-algorithms-in-javascript

#include "Arduino.h"

class Color {
  unsigned short red, green, blue;

  public:
    void set_rgb(unsigned short* rgb){ 
      this->red = rgb[0]; this->green = rgb[1]; this->blue = rgb[2];
    }
    void get_rgb(unsigned short* rgb){
      rgb[0] = this->red; rgb[1] = this->green; rgb[2] = this->blue;
    }
    void set_hsl(unsigned short* hsl){
      unsigned short rgb[3] = {0,0,0};
      hsl_to_rgb(hsl,rgb);
      set_rgb(rgb);
    }
    void get_hsl(unsigned short* hsl){ unsigned short* rgb; get_rgb(rgb); rgb_to_hsl(rgb,hsl); }
    void print_hsl();
    void print_rgb();

    //void set_hsl(unsigned short* hsl);
    //void get_hsl(unsigned short* hsl);

    void rgb_to_hsl(unsigned short* rgb, unsigned short *hsl);
    void hsl_to_rgb(unsigned short* hsl, unsigned short *rgb);

};

void Color::rgb_to_hsl( unsigned short * rgb, unsigned short * hsl) {
  float red, green, blue, min, max, chroma;
  red   = rgb[0] / 255;
  green = rgb[1] / 255;
  blue  = rgb[2] / 255;
  max = max( red, max( green, blue ) );
  min = min( red, min( green, blue ) );
  chroma = max - min;

  //unsigned short hue = 0, sat = 0, lum = 0;

  //lum = (min + max) / 2;

  if (max == min) {
    hue = sat = 0;
  } else {
    float diff = max - min;
    if (lum > 0.5) {
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

  //hsl[0] = hue;
  //hsl[1] = sat;
  //hsl[2] = lum;
}


/* hue => [0,360], sat => [0,100], lum => [0,100] */
void Color::hsl_to_rgb( unsigned short * hsl, unsigned short * rgb) {
  float chroma, x, sat, lum, red, green, blue;
  int hue;
  hue = hsl[0]; sat = hsl[1] / 100.0; lum = hsl[2] / 100.0;

  //chroma = sat * ( 1- |2*lum - 1|)
  chroma = sat * ( 1 - abs(2 * lum - 1) );

  //hue' = hue / 60
  hue = hsl[0] / 60;

  //x = chroma * (1- |hue' % 2-1|)
  x = chroma * ( 1- abs(hue % 2 -1) );

  if      (hue >= 0 && hue < 1) { red = chroma;  green = x;       blue = 0;      }
  else if (hue >= 1 && hue < 2) { red = x;       green = chroma;  blue = 0;      }
  else if (hue >= 2 && hue < 3) { red = 0;       green = chroma;  blue = x;      }
  else if (hue >= 3 && hue < 4) { red = 0;       green = x;       blue = chroma; }
  else if (hue >= 4 && hue < 5) { red = x;       green = 0;       blue = chroma; }
  else if (hue >= 5 && hue < 6) { red = chroma;  green = 0;       blue = x;      }
  else                          { red = 0;       green = 0;       blue = 0;      }

  x = lum - chroma * 0.5;
  rgb[0] = 255 * (red + x);
  rgb[1] = 255 * (green + x);
  rgb[2] = 255 * (blue + x);
}

void Color::print_rgb(){
  Serial.print("red: ");
  Serial.print( red );
  Serial.print(" green: ");
  Serial.print( green );
  Serial.print(" blue: ");
  Serial.println( blue );
}

void Color::print_hsl(){
  unsigned short hsl[3];
  unsigned short rgb[3] = { red, green, blue };

  rgb_to_hsl(rgb,hsl);

  Serial.print("hue: ");
  Serial.print(hsl[0]);
  Serial.print(" sat: ");
  Serial.print(hsl[1]);
  Serial.print(" lum: ");
  Serial.println(hsl[2]);
}
