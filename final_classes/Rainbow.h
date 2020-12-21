#include "Arduino.h";

class Rainbow {
  public:
  Rainbow() {}
  void runPattern(CRGB* leds);
};

void Rainbow::runPattern(CRGB* leds) {
  fill_rainbow(leds, numLeds, 0, 255/numLeds);
}
