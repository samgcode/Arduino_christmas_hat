#include "Arduino.h";

class FadeHue {
  public:
  FadeHue(int numLeds) {
    _numLeds = numLeds;  
  }
  void solid(CRGB* leds);
  void perLED(CRGB* leds);

  private:
  int _state = 0;
  int _maxState = 255;
  int _numLeds = 0;
  int _speed = 15;
  void updateState();
};

void FadeHue::solid(CRGB* leds) {
  fill_solid(leds, numLeds, CHSV(_state, 255, 255));
  EVERY_N_MILLISECONDS(_speed) {
    updateState();
  }
}

void FadeHue::perLED(CRGB* leds) {
  for(int led = 0; led < _numLeds; led++) {
    leds[led] = CHSV(_state + (led*15), 255, 255);
  }
  EVERY_N_MILLISECONDS(_speed) {
    updateState();
  }
}

void FadeHue::updateState() {
  _state++;
  if(_state > _maxState) {
    _state = 0;
  }
}
