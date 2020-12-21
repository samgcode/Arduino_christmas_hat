int red = 8;
int blue = 9;
int green = 10;

int switchPin = 11;
int buttonPin = 12;

int animation = 0;

unsigned long prevMillis = 0;
unsigned long currentMillis = 0;

int animId = 0;
int anim0States[5][3] = {
  {1, 0, 0},
  {1, 1, 0},
  {0, 1, 0},
  {0, 1, 1},
  {0, 0, 1}
};

int anim1States[3][3] = {
  {1, 0, 0},
  {0, 1, 0},
  {0, 0, 1}
};

void setup()
{
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(switchPin, INPUT);
  pinMode(buttonPin, INPUT);
  Serial.begin(9600);
}

int changeTime = 250;
void loop()
{
  Serial.println(digitalRead(switchPin));
  currentMillis = millis();
  if(digitalRead(buttonPin) == HIGH) {
    animation += 1;
  }
  if(digitalRead(switchPin) == HIGH) {
    writeColor(0, 1, 0);
//    if(animation == 0) {
//       animation1(); 
//    } else if(animation == 1) {
//      animation1(); 
//    }
       
  } else {
    writeColor(0, 0, 0);
  }
}

void writeColor(int r, int g, int b) {
  digitalWrite(red, 1-r); 
    digitalWrite(green, 1-g);
    digitalWrite(blue, 1-b); 
}


void animation0() {
  if (currentMillis - prevMillis >= changeTime) {
    prevMillis = millis();
    writeColor(
        anim0States[animId][0], 
      anim0States[animId][1], 
      anim0States[animId][2]
     );
    animId+=1;
    if(animId >= 5) {
      animId = 0;
    }
  }
}

void animation1() {
  if (currentMillis - prevMillis >= changeTime) {
    prevMillis = millis();
    writeColor(
        anim1States[animId][0], 
      anim1States[animId][1], 
      anim1States[animId][2]
     );
    animId+=1;
    if(animId >= 3) {
      animId = 0;
    }
  }
}
