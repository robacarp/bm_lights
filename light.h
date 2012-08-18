#include "color.h"
#include "Arduino.h"

//this abstraction may now be superfluous, but ideally lights 
//  also have a position and vector
class Light {
  public:
    Color color;
};
