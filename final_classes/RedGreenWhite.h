#include "Arduino.h";
#include <FastLED.h>

class RedGreenWhite {
  public:
  RedGreenWhite(int numLeds) {
    _numLeds = numLeds;  
    for(int i = 0; i < numLeds; i++) {
      _colorIndex[i] = random8();
    }
  }
  void wave(CRGB* leds);
  void gradient(CRGB* leds);

  private:
  uint8_t _colorIndex[numLeds];
  int _numLeds = 0;
//  DEFINE_GRADIENT_PALETTE(redGreenWhite_gp) {
//    0, 255, 0, 0,
//    64, 0, 255, 0,
//    191, 255, 255, 255,
//    255, 255, 0, 0
//  };
  
  CRGBPalette16 RGW = {
    0xff0000,
    0x00ff00,
    0xffffff,
    0xff0000
  };
};

void RedGreenWhite::wave(CRGB* leds) {
  uint8_t sinBeat1 = beatsin8(30, 0, numLeds-1, 0, 0);
  uint8_t sinBeat2 = beatsin8(30, 0, numLeds-1, 0, 85);
  uint8_t sinBeat3 = beatsin8(30, 0, numLeds-1, 0, 170);

  leds[sinBeat1] = CRGB::Red;
  leds[sinBeat2] = CRGB::Green;
  leds[sinBeat3] = CRGB::White;
  
  fadeToBlackBy(leds, _numLeds, 1);
}

void RedGreenWhite::gradient(CRGB* leds) {
  for(int led = 0; led < numLeds; led++) {
    leds[led] = ColorFromPalette(RGW, _colorIndex[led]);
  }
  EVERY_N_MILLISECONDS(5) {
    for(int i = 0; i < numLeds; i++) {
      _colorIndex[i]++;
    }
  }
}
