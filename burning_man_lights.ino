// pin mappings
#define DATA 11
#define LATCH 9
#define ENABLE 10
#define CLOCK 13

// button needs to be on 3 (INT1) for interrupt to work correctly
#define BUTTON 3

//algorithm speed/delay
#define DELAY 10
#define INCREMENT 1

#define NUM_LIGHTS 2
#include "light.h"

Light * lights[NUM_LIGHTS];
unsigned long tick;
unsigned int algorithm_pick;
bool next_algorithm = false;
unsigned long last_algorithm_advance;

//the current lighting algorithm
void (*fxn)(Light *, int, unsigned long);

void setup(){
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(ENABLE, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(BUTTON, INPUT);

  digitalWrite(ENABLE, 0);
  digitalWrite(LATCH, 0);

  //enable internal pull-up resistor;
  //connect button between this pin and ground
  digitalWrite(BUTTON, 1);

  //attach the interrup handler to that pin
  attachInterrupt(1, button_interrupt, FALLING);

  for (int i = 0; i < NUM_LIGHTS; i ++){
    lights[i] = new Light;
    lights[i]->color.set_rgb(0,0,0);
    set_brightness(128);
  }

  tick = 0;
  algorithm_pick = 0;
  last_algorithm_advance = millis();

  //don't not do this.
  fxn = &rainbow;
}

void loop(){
  switch_algorithms();
  increment_algorithm();
  update_lights();
  delay(DELAY);
}

void increment_algorithm(){
  tick += INCREMENT;

  for (int i=0; i<NUM_LIGHTS; i++)
    (*fxn)(lights[i], i, tick);
}

