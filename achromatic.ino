void achromatic(Light * light, int position, unsigned long tick){
  int brightness = 0;
  //visible seems to run from about brightness:20-100
  int shift = ((tick + (position * 20)) % 160);

  if (shift >= 80){
    brightness = 20 + shift - 80;
  } else {
    brightness = 100 - shift;
  }

  light->color.set_hsb( 0, 0, brightness);
}
