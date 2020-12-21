#include <Adafruit_NeoPixel.h>
int pin = 9;
int nextButton = 3;
int colorButton = 2;
int animation = 0;
int color = 0;
const int maxAnimation = 26;
const int maxColor = 100;
int state = 0;
int fadeState = 0;
int maxState = 0;
int numberOfLeds = 10;

unsigned long lastDebounceTimeNext = 0;
unsigned long debounceDelay = 500;
unsigned long lastDebounceTimeColor = 0;
unsigned long prevChangeTime = 0;

typedef void (*animFn)();
typedef void (*colorFn)(int);

static animFn animations[maxAnimation];
static colorFn colors[maxColor];


Adafruit_NeoPixel strip = Adafruit_NeoPixel(
  numberOfLeds, pin, NEO_RGB + NEO_KHZ800
);

void setup()
{
  pinMode(nextButton, INPUT);
  pinMode(colorButton, INPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show();
  animations[0] = solid;
  animations[1] = solidBlink;
  animations[2] = solid;

  colors[0] = off;
  colors[1] = red;
  colors[2] = green;
  colors[3] = blue;
  colors[4] = purple;
  colors[5] = yellow;
  colors[6] = cyan;
  colors[7] = white;
  randomSeed(analogRead(0));
  attachInterrupt(digitalPinToInterrupt(colorButton), nextColor, RISING);
  attachInterrupt(digitalPinToInterrupt(nextButton), nextAnimation, RISING);
}

int led = 0;
int changeTime = 200;
int defaultC = 200;
void loop()
{
  updateState();
//  animation = 0;
//  color = 1;
  animations[animation]();
}

void updateState() {
  Serial.print("animation: ");
  Serial.print(animation);
  Serial.print("  color: ");
  Serial.println(color);
  
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
      if(color > maxColor) {
        color = 0;
      }
  }
  lastDebounceTimeColor = currentTime;
}

//<color-functions>

void writeColor(int led) {
  colors[color](led);
}

void writeToLed(int led, int r, int g, int b) {
  strip.setPixelColor(led, r, g, b);
}

void off(int led) {
  writeToLed(led, 0, 0, 0);
}

void red(int led) {
  writeToLed(led, 255, 0, 0);
}


void green(int led) {
  writeToLed(led, 0, 255, 0);
}

void blue(int led) {
  writeToLed(led, 0, 0, 255);
}

void purple(int led) {
  writeToLed(led, 255, 0, 255);
}

void yellow(int led) {
  writeToLed(led, 255, 255, 0);
}

void cyan(int led) {
  writeToLed(led, 0, 255, 255);
}

void white(int led) {
  writeToLed(led, 255, 255, 255);
}

//</color-functions>

//<animation-functions>

void solid() {
  for(int i = 0; i < numberOfLeds; i++) {
    writeColor(i);
  }
  strip.show();
}

void solidBlink() {
  maxState = 1;
  for(int i = 0; i < numberOfLeds; i++) {
    if(state == 0) {
      writeColor(i); 
    } else {
      off(i);
    }
  }
  strip.show();
}

//</animation-functions>
