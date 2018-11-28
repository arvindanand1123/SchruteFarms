//The buttons need to be plugged into digital input pins.
//The leds need to be pluged into PMW pins.
const int greenLED = 5;     const int greenButton = 22;      int greenState = 0;
const int blueLED = 6;   const int blueButton = 24;     int blueState = 0;
const int redLED = 7;      const int redButton = 26;        int redState = 0;

int green = 0;              int currentGreen = 0;
int blue = 0;             int currentBlue = 0;
int red = 0;                int currentRed= 0;

int tenth = 25;

int greenFade = 1;          int blueFade = 3;            int redFade = 5;


void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);

}

void loop() {
  greenState = digitalRead(greenButton);
  blueState = digitalRead(blueButton);
  redState = digitalRead(redButton);

//GreenButton Protocol
  if (greenState == LOW){
    delay(100);
    green = currentGreen + tenth;
 
    if (green > 255){
      analogWrite(greenLED, 255);
      currentGreen = 255;
    }
    else {
      analogWrite(greenLED, green);
      currentGreen = green;
    }
  }

  if ((greenState == HIGH)&&(currentGreen > 0)) {
    green = currentGreen - greenFade;

    if (green < 0){
      analogWrite(greenLED, 0);
      currentGreen = 0;
    }
    else {
      delay(25);
      analogWrite(greenLED, green);
      currentGreen = green;
    }
    
  }
//blueButton Protocol
  if (blueState == LOW){
    delay(100);
    blue = currentBlue + tenth;
 
    if (blue > 255){
      analogWrite(blueLED, 255);
      currentBlue = 255;
    }
    else {
      analogWrite(blueLED, blue);
      currentBlue = blue;
    }
  }

  if ((blueState == HIGH)&&(currentBlue > 0)) {
    blue = currentBlue - blueFade;

    if (blue < 0){
      analogWrite(blueLED, 0);
      currentBlue = 0;
    }
    else {
      delay(25);
      analogWrite(blueLED, blue);
      currentBlue = blue;
    }
    
  }
//RedButton Protocol
  if (redState == LOW){
    delay(100);
    red = currentRed + tenth;
 
    if (red > 255){
      analogWrite(redLED, 255);
      currentRed = 255;
    }
    else {
      analogWrite(redLED, red);
      currentRed = red;
    }
  }

  if ((redState == HIGH)&&(currentRed > 0)) {
    red = currentRed- redFade;

    if (red < 0){
      analogWrite(redLED, 0);
      currentRed = 0;
    }
    else {
      delay(25);
      analogWrite(redLED, red);
      currentRed = red;
    }
  }  
}
