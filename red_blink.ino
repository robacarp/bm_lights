void red_blink(Light * light, int position, unsigned long tick){
  int bright = tick % 100 > 50 ? 100 : 0;
  light->color.set_hsb( 1, 100, bright);
}
