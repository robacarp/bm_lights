// pin mappings
#define DATA 11
#define LATCH 9
#define ENABLE 10
#define CLOCK 13

//algorithm speed/delay
#define DELAY 10
#define INCREMENT 1

#define DEBUG

#define NUM_LIGHTS 2
#include "light.h"

Light * lights[NUM_LIGHTS];
unsigned long tick;

void setup(){
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(CLOCK, OUTPUT);

  digitalWrite(ENABLE, 0);
  digitalWrite(LATCH, 0);

#ifdef DEBUG
  Serial.begin(115200);
#endif

  for (int i = 0; i < NUM_LIGHTS; i ++){
    lights[i] = new Light;
    lights[i]->color.set_rgb(0,0,0);
    set_brightness(128);
  }

  tick = 0;
}

void loop(){
  increment_algorithm();
  update_lights();
  delay(DELAY);
}

void increment_algorithm(){
  tick += INCREMENT;
  Serial.println(tick);
  for (int i=0; i<NUM_LIGHTS; i++)
    rainbow(lights[i], i, tick);
}

