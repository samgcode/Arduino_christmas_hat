#include <FastLED.h>

const int numLeds = 10;
const int pin = 9;
const int nextButton = 3;
const int colorButton = 2;
const int maxAnimation = 16;
const int maxColor = 8;

int animation = 0;
int color = 0;
int state = 0;
int fadeState = 0;
int maxState = 0;
int changeTime = 200;

unsigned long lastDebounceTimeNext = 0;
unsigned long debounceDelay = 300;
unsigned long lastDebounceTimeColor = 0;
unsigned long prevChangeTime = 0;

typedef void (*animFn)();

static animFn animations[maxAnimation];
static CRGB colors[maxColor];


CRGB leds[numLeds];

void setup() {
  pinMode(nextButton, INPUT);
  pinMode(colorButton, INPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  
  FastLED.addLeds<WS2812B, pin, RGB>(leds, numLeds);
  FastLED.setBrightness(100);
  clear();
  update();

  animations[0] = solid;
  animations[1] = solidBlink;
  animations[2] = moveOneWay;
  animations[3] = moveTwoWay;
  animations[4] = rainbow;
  animations[5] = rainbow;
  animations[6] = rainbow;
  animations[7] = rainbow;
  animations[8] = rainbow;
  animations[9] = rainbow;
  animations[10] = rainbow;
  animations[11] = rainbow;
  animations[12] = rainbow;
  animations[13] = rainbow;
  animations[14] = rainbow;
  animations[15] = rainbow;
  animations[16] = rainbow;


  colors[0] = CRGB::Black;
  colors[1] = CRGB::Red;
  colors[2] = CRGB::Green;
  colors[3] = CRGB::Blue;
  colors[4] = CRGB::Yellow;
  colors[5] = CRGB::Magenta;
  colors[6] = CRGB::Cyan;
  colors[7] = CRGB::White;
  
  attachInterrupt(digitalPinToInterrupt(colorButton), nextColor, RISING);
  attachInterrupt(digitalPinToInterrupt(nextButton), nextAnimation, RISING);
}

void loop() {
  updateState();
  animations[animation]();
  update();
}

void update() {
  FastLED.show();
}

void clear() {
  fill_solid(leds, numLeds, CRGB::Black);
}

void updateState() {
//  Serial.print("animation: ");
  Serial.print(animation);
//  Serial.print("  color: ");
//  Serial.println(color);
  
  if ((millis() - prevChangeTime) > changeTime) {
    state++;
    if(state > maxState) {
      state = 0;
      fadeState++;
    }
    prevChangeTime = millis();
  }
}

void nextAnimation() {  
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTimeNext) > debounceDelay) {
     animation++;
      if(animation > maxAnimation) {
        Serial.print("Test");
        animation = 0;
      }
      state = 0;
  }

  lastDebounceTimeNext = currentTime;
}

void nextColor() {  
  unsigned long currentTime = millis();
  if((currentTime - lastDebounceTimeColor) > debounceDelay) {
     color++;
      if(color >= maxColor) {
        color = 0;
      }
  }
  lastDebounceTimeColor = currentTime;
}

//<animation-functions>

void solid() {
  fill_solid(leds, numLeds, colors[color]);
}

void solidBlink() {
  changeTime = 200;
  maxState = 1;
  if(state == 0) {
    fill_solid(leds, numLeds, colors[color]);
  } else {
    clear();
  }
}

void rainbow() {
  fill_rainbow(leds, numLeds, 0, 255 / numLeds);
}

void moveOneWay() {
  changeTime = 100;
  maxState = numLeds;
    clear();
    leds[state] = colors[color];
}

void moveTwoWay() {
  changeTime = 100;
  maxState = numLeds*2;
  if(maxState < numLeds) {
    clear();
    leds[state] = colors[color];
  } else {
    clear();
    leds[state - numLeds] = colors[color];
  }
}

//</animation-functions>


























































//
