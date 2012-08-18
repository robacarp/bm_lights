//the whole rainbow, unmoving, unchanging
//
//NOTE: I'm sort of guessing the math is right here
//      as it's not really testable with only two lights :)
void static_rainbow(Light * light, int position, unsigned long tick){
 //30 here is the offset between lights.
 //you'll probably want to change it depending on 
 //how far apart the lights are

  int hue = position * (360 / NUM_LIGHTS);
  light->color.set_hsb( hue, 100, 100);
}
