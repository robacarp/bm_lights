void switch_algorithms(){
  if (next_algorithm) {

    // sort of a poor-mans debounce.
    if (millis() - last_algorithm_advance < 400) {
      next_algorithm = false;
      return;
    }

    last_algorithm_advance = millis();

    next_algorithm = false;
    algorithm_pick ++;

    if (algorithm_pick > 4)
      algorithm_pick = 0;

    switch (algorithm_pick) {
      case 0: fxn = &rainbow; break;
      case 1: fxn = &pink; break;
      case 2: fxn = &unified_rainbow; break;
      case 3: fxn = &static_rainbow; break;
      case 4: fxn = &achromatic; break;

      // red blinking means something broke...
      default: fxn = &red_blink; break;
    }
  }
}

void button_interrupt(){
  next_algorithm = true;
}

