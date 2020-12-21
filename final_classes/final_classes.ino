#include <FastLED.h>

const int numLeds = 10;
const int colorBtnPin = 2;
const int animBtnPin = 3;
const int ledPin = 9;
const int maxAnimation = 4;

int animation = 0;
int color = 1;
int state = 0;
int fadeState = 0;
int maxState = 0;
int changeTime = 200;
int blendAmount = 0;

unsigned long lastDebounceTimeNext = 0;
unsigned long debounceDelay = 300;
unsigned long lastDebounceTimeColor = 0;
unsigned long prevChangeTime = 0;

bool useLeds1 = true;

typedef void (*animFn)();

static animFn animations[maxAnimation];

CRGB leds[numLeds];
CRGB leds2[numLeds];
CRGB output[numLeds];
uint8_t colorIndex[numLeds];

#include "Rainbow.h"
#include "FadeHue.h"
#include "RedGreenWhite.h"
Rainbow rainbow = Rainbow();
FadeHue fadeHue = FadeHue(numLeds);
RedGreenWhite rgw = RedGreenWhite(numLeds);

void setup() { 
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  FastLED.addLeds<WS2812, ledPin, RGB>(output, numLeds);
  FastLED.setBrightness(100);
  FastLED.setCorrection(UncorrectedColor);
  clear();
  update();

  for(int i = 0; i < numLeds; i++) {
    colorIndex[i] = random8();
  }

  attachInterrupt(digitalPinToInterrupt(colorBtnPin), prevAnimation, RISING);
  attachInterrupt(digitalPinToInterrupt(animBtnPin), nextAnimation, RISING);
  animation = 0;
}

void loop() {  
//  EVERY_N_MILLISECONDS(10) {
//    clear();
//    blend(leds, leds2, output, numLeds, blendAmount);
//    if(!useLeds1) {
//      if(blendAmount < 255) {
//        blendAmount++; 
//      }
//    } else {
//      if(blendAmount > 0) {
//        blendAmount--;
//      }
//    }
//  }
//    fadeHue.solid(output);
    showState();
    updateLEDs(output, animation);
//    updateLEDs(leds2, animation+1);
    update();
}

void update() {
  FastLED.show();
}

void clear() {
  fill_solid(output, numLeds, CRGB::Black);
}

void showState() {
  Serial.print("animation: ");
  Serial.print(animation);
  Serial.print("  color: ");
  Serial.print(color);
  Serial.print("  blend: ");
  Serial.println(blendAmount);
}

void nextAnimation() {  
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTimeNext) > debounceDelay) {
     animation++;
     useLeds1 = !useLeds1;
    if(animation > maxAnimation) {
      animation = 0;
    }
    state = 0;
  }

  lastDebounceTimeNext = currentTime;
}

void prevAnimation() {  
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTimeColor) > debounceDelay) {
     animation--;
      if(animation < 0) {
        animation = maxAnimation;
      }
  }
  lastDebounceTimeColor = currentTime;
}



//<run animation functions>


void updateLEDs(CRGB* leds, int animation) {
  switch(animation) {
    case 0:
      rainbow.runPattern(leds);
      break;
    case 1:
      fadeHue.solid(leds);
      break;
    case 2:
      fadeHue.perLED(leds);
      break;
    case 3:
      rgw.wave(leds);
      break;
    case 4:
      rgw.gradient(leds);
      break;
  }
}
       

//</run animation functions>


























///
