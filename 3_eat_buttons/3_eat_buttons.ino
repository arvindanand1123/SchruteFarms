//The buttons need to be plugged into digital input pins.
//The leds need to be pluged into PMW pins.

const int greenLED = 9;     const int greenButton = 2;      int greenState = 0;
const int yellowLED = 10;   const int yellowButton = 3;     int yellowState = 0;
const int redLED = 11;      const int redButton = 4;        int redState = 0;

int green = 0;              int currentGreen = 0;
int yellow = 0;             int currentYellow = 0;
int red = 0;                int currentRed= 0;

int tenth = 25;

int greenFade = 1;          int yellowFade = 3;            int redFade = 5;


void setup() {
  pinMode(greenLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(yellowButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);

}

void loop() {
  greenState = digitalRead(greenButton);
  yellowState = digitalRead(yellowButton);
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
//YellowButton Protocol
  if (yellowState == LOW){
    delay(100);
    yellow = currentYellow + tenth;
 
    if (yellow > 255){
      analogWrite(yellowLED, 255);
      currentYellow = 255;
    }
    else {
      analogWrite(yellowLED, yellow);
      currentYellow = yellow;
    }
  }

  if ((yellowState == HIGH)&&(currentYellow > 0)) {
    yellow = currentYellow - yellowFade;

    if (yellow < 0){
      analogWrite(yellowLED, 0);
      currentYellow = 0;
    }
    else {
      delay(25);
      analogWrite(yellowLED, yellow);
      currentYellow = yellow;
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
