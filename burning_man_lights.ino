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
unsigned int algorithm_pick;

//the current lighting algorithm
void (*fxn)(Light *, int, unsigned long);

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
  algorithm_pick = 4;
}

void loop(){
  increment_algorithm();
  update_lights();
  delay(DELAY);
}

void increment_algorithm(){
  tick += INCREMENT;

  switch (algorithm_pick) {
    case 0: fxn = &rainbow; break;
    case 1: fxn = &pink; break;
    case 2: fxn = &unified_rainbow; break;
    case 3: fxn = &static_rainbow; break;
    case 4: fxn = &achromatic; break;
  }

  for (int i=0; i<NUM_LIGHTS; i++)
    (*fxn)(lights[i], i, tick);
}

