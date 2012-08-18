//runs through the whole rainbow
void rainbow(Light * light, int position, unsigned long tick){
 //30 here is the offset between lights.
 //you'll probably want to change it depending on 
 //how far apart the lights are

  int hue = (tick + (30 * position)) % 360;
  light->color.set_hsb( hue, 100, 100);
}
