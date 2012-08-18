// sort of vascillates between a blueish and a redish pink
void pink(Light * light, int position, unsigned long tick){
  //pink runs from about hue:285-325
  int hue;
  int shift = ((tick + (position * 20)) % 80);

  if (shift >= 40){
    // hue going up
    hue = 285 + shift - 40;
  } else {
    // hue going back down
    hue = 325 - shift;
  }

  light->color.set_hsb( hue, 100, 100);
}
