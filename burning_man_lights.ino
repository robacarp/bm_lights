#include "color.h"

Color c;
unsigned short rgb[3] = {76,155,205};
unsigned short hsl[3] = {0,0,50};

void setup(){
  Serial.begin(9600);
}

void loop(){
  c.set_hsl(hsl);
  c.print_rgb();

  while (1)
    delay(300);
}

