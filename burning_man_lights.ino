#define DATA 11
#define LATCH 9
#define ENABLE 10
#define CLOCK 13

//#define DEBUG

#define NUM_LIGHTS 2
#include "light.h"

Light * lights[NUM_LIGHTS];
Color c;
int rgb[3];
int hsb[3];
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
  delay(10);
}

void increment_algorithm(){
  tick ++;
  for (int i=0; i<NUM_LIGHTS; i++)
  //  lights[i]->color.set_hsb(tick, 50,100);
    rainbow(lights[i], i, tick);
}

#ifdef DEBUG
void debug_lights(){
  for (int i=0; i<NUM_LIGHTS; i++) {
    Serial.print("Light #");
    Serial.print(i);
    Serial.print(": ");
    lights[i]->color.print_rgb();
  }
}
#endif

void rainbow(Light * light, int position, int tick){
  int hue = (tick + (30 * position)) % 360;
  light->color.set_hsb( hue, 255, 128);
}

void update_lights(){
  digitalWrite(ENABLE,1);

  for (int i=0; i < NUM_LIGHTS; i++){
    update_light(
        (int) lights[i]->color.red << 2,
        (int) lights[i]->color.green << 2,
        (int) lights[i]->color.blue << 2
        );
  }

  digitalWrite(ENABLE,0);
}

void set_brightness(int val){
  //write to current control register
  unsigned long packet = B01 & B11;
  packet = (packet << 10) | (val & 1023);
  packet = (packet << 10) | (val & 1023);
  packet = (packet << 10) | (val & 1023);
  send_packet(packet);
}

// expects colors to be in 1024 notation
void update_light(int r, int g, int b){
  unsigned long packet;

  //round off the colors
  if (r > 1023) r = 1023; if (r < 0) r = 0;
  if (g > 1023) g = 1023; if (g < 0) g = 0;
  if (b > 1023) b = 1023; if (b < 0) b = 0;

  //write to pwm register
  packet = B00 & B11;
  packet = (packet << 10) | (b & 1023);
  packet = (packet << 10) | (r & 1023);
  packet = (packet << 10) | (g & 1023);
  send_packet(packet);
}

void send_packet(unsigned long packet){
  shiftOut(DATA, CLOCK, MSBFIRST, packet >> 24);
  shiftOut(DATA, CLOCK, MSBFIRST, packet >> 16);
  shiftOut(DATA, CLOCK, MSBFIRST, packet >> 8);
  shiftOut(DATA, CLOCK, MSBFIRST, packet);

  delay(1);
  digitalWrite(LATCH, 1);
  delay(1);
  digitalWrite(LATCH, 0);
}
