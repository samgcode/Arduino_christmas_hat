#include <Adafruit_NeoPixel.h>

int pin = 2;
int buttonPin = 3;
int animation = -1;
int maxAnimation = 11;
int state = 0;
int fadeState = 0;
int maxState = 0;
int numberOfLeds = 10;

int buttonState = 0;
int lastButtonState = 0;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 5;
unsigned long prevChangeTime = 0;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(
  numberOfLeds, pin, NEO_RGB + NEO_KHZ800
);

void setup()
{
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
  strip.begin();
  strip.show();
}

int led = 0;
int changeTime = 200;
int defaultC = 200;
void loop()
{
  int reading = !digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == 1) {
        animation++;
        if(animation > maxAnimation) {
          animation = 0;
        }
        state = 0;
      }
    }
  }
  lastButtonState = reading;

  if ((millis() - prevChangeTime) > changeTime) {
    state++;
    if(state > maxState) {
      state = 0;
      fadeState++;
    }
    prevChangeTime = millis();
  }

  if(animation == 0) {
    empty();
  } else if(animation == 1) {
    fullRed();
  } else if(animation == 2) {
    fullGreen(); 
  } else if(animation == 3) {
    fullBlue(); 
  } else if(animation == 4) {
    fullBright(); 
  } else if(animation == 5) {
    changeTime = 200;
    redGreenPattern();
  } else if(animation == 6) {
    changeTime = 200;
    redWhiteGreen();
  } else if(animation == 7) {
    changeTime = 80;
    singleRedMoving();
  } else if(animation == 8) {
    changeTime = 80;
    singleGreenMoving();
  } else if(animation == 9) {
    changeTime = 80;
    singleBlueMoving();
  } else if(animation == 10) {
    changeTime = 20;
    fadeRGB();
  } else if(animation == 11) {
    changeTime = 20;
    fadeRBG();
  }
}

void writeToLed(int led, int r, int g, int b) {
  strip.setPixelColor(led, r, g, b);
  strip.show();
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

void empty() {
  for(int i = 0; i < numberOfLeds; i++) {
    off(i);
  }
}

void fullRed() {
  for(int i = 0; i < numberOfLeds; i++) {
    red(i);
  }
}

void fullGreen() {
  for(int i = 0; i < numberOfLeds; i++) {
    green(i);
  }
}

void fullBlue() {
  for(int i = 0; i < numberOfLeds; i++) {
    blue(i);
  }
}

void fullBright() {
  for(int i = 0; i < numberOfLeds; i++) {
    white(i);
  }
}

void redGreenPattern() {
  maxState = 1;
  if(state == 0) {
   for(int i = 0; i < numberOfLeds; i++) {
      if(i % 2 == 0) {
        red(i);
      } else {
        green(i);
      }
    }
  } else if(state == 1) {
    for(int i = 0; i < numberOfLeds; i++) {
      if(i % 2 == 0) {
        green(i);
      } else {
        red(i);
      }
    }
  }
}

void redWhiteGreen() {
  maxState = 2;
  int count;
  if(state == 0) {
    count = 0;
    for(int i = 0; i < numberOfLeds; i++) {
      if(count == 0) {
        red(i);
      } else if(count == 1) {
       white(i);
      } else if(count == 2) {
        green(i);
      }
      count++;
      if(count >= 3) {
        count = 0;
      }
    } 
  } else if(state == 1) {
    count = 0;
    for(int i = 0; i < numberOfLeds; i++) {
      if(count == 0) {
        green(i);
      } else if(count == 1) {
        red(i);
      } else if(count == 2) {
        white(i);
      }
      count++;
      if(count >= 3) {
        count = 0;
      }
    }
  } else if(state == 2) {
    count = 0;
    for(int i = 0; i < numberOfLeds; i++) {
      if(count == 0) {
        white(i);
      } else if(count == 1) {
        green(i);
      } else if(count == 2) {
        red(i);
      }
      count++;
      if(count >= 3) {
        count = 0;
      }
    } 
  } 
}

void singleRedMoving() {
  maxState = numberOfLeds;
  empty();
  red(state);
}

void singleGreenMoving() {
  maxState = numberOfLeds;
  empty();
  green(state);
}

void singleBlueMoving() {
  maxState = numberOfLeds;
  empty();
  blue(state);
}

void fadeRGB() {
  maxState = 255;
  int r = 255;
  int g = 0;
  int b = 0;

  if(fadeState == 0) {
    r = 255 - state;
    g = 0 + state;
    b = 0;
  }
  if(fadeState == 1) {
    r = 0;
    g = 255 - state;
    b = 0 + state;
  }
  if(fadeState == 2) {
    r = 0 + state;
    g = 0;
    b = 255 - state;
  }
  if(fadeState >= 3) {
    fadeState = 0;
  }
    
  for(int i = 0; i < numberOfLeds; i++) {
    writeToLed(i, r, g, b);
  }
}

void fadeRBG() {
  maxState = 255;
  int r = 255;
  int g = 0;
  int b = 0;

  if(fadeState == 0) {
    r = 255 - state;
    g = 0;
    b = 0 + state;
  }
  if(fadeState == 1) {
    r = 0;
    g = 255 + state;
    b = 255 - state;
  }
  if(fadeState == 2) {
    r = 0 + state;
    g = 255 - state;
    b = 0;
  }
  if(fadeState >= 3) {
    fadeState = 0;
  }
    
  for(int i = 0; i < numberOfLeds; i++) {
    writeToLed(i, r, g, b);
  } 
}







/*
 * TODO0
 * - set max animations
 * - make more animations
 */


//
