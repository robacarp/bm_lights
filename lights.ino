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
