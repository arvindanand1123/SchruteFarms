// Adafruit PN532 - Version: Latest 
//IMPORT STATEMENTS
#include <Wire.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_PN532.h>
#include "animal.h"
using namespace std;

//RFID Adafruit Breakout Board instantiation
//Adafruit_PN532 nfc(2, 5, 3, 4);
#define PN532_IRQ   (2)
#define PN532_RESET (3)
Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);

//LCD instantiation
SoftwareSerial LCD(10, 11);

//global variables
int counter = 0;
bool isDone = false;

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


//Arduino setup
void setup() {
  //LCD
  LCD.begin(9600);
  systemReady();
  //.................

  //RFID Setup
  Serial.begin(9600);
  Serial.println("Hello!");

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
  Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
  Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
  
  // configure board to read RFID tags
  nfc.SAMConfig();
  
  Serial.println("Waiting for an ISO14443A Card ...");
  //.......................................................
  
  //Animals Setup
  SetupAnimals();

  //LED Setup
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenButton, INPUT_PULLUP);
  pinMode(blueButton, INPUT_PULLUP);
  pinMode(redButton, INPUT_PULLUP);
  //...............................
}

void loop() {
  //
  String input = readRFID();
  //If the RFID reads the reset tag, then the system resets
  if(input.equals("f6566f7e")){reset();}
  //If reset isn't read, then it checks to see if the students are "done" with placing the animals on the board --> enters LED mode
  if(isDone){playLED();}
  //If reset isn't read, then it checks to see if an animal is present and if it's in the correct spot --> calls the function
  if(input!="0000"){isAnimal(input);}
  //enables LED functionality
}

//Contains LED code for all 3 buttons
void playLED(){
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

//Checks if the RFID scanned is one of the animal hex values
void isAnimal(String str){
  //linear search through animals array
  for(int i = 0; i < animalCount; i++){
    if(animals[i].getHex() == str){
      String input = readRFID();
      while(true){
        if(input != str){
          break;
        } else {
          input = readRFID();   
        }
      }
      if(animals[i].getLoc().equals(input) && animals[i].getFound() == false){
        Serial.println("Location Found for " + animals[i].getName());
        animals[i].setFound(true);
        counter++;
        break;
      } 
      else if(!animals[i].getLoc().equals(input) && animals[i].getFound() == false){
        Serial.println(animals[i].getName() + " in the wrong location.");
        animals[i].setFound(true);
        break;
      }
    }
    
  }
  updateLCD();
}

void updateLCD(){
  int temp = 0;
  
  for(int i = 0; i < animalCount; i++){
    if(animals[i].getFound() == true){
      temp++;
    }
  }
  writeToLCD(("Animals Read:" + String(temp)).c_str());
  if(temp == animalCount){
    isDone = true;
    if(counter == 16){
      writeToLCD("Correct! Nice work!");
    } else {
      writeToLCD((String(counter) + " out of 16 are correct").c_str());
    }
    delay(3000);
    writeToLCD("Play with the Buttons!");
    delay(3000);
    writeToLCD("OR");
    delay(1000);
    writeToLCD("Scan reset to try again");
  }
  
}

//method for reseting system
void reset(){
  //Makes it so that all the animals can be scanned again
  for(int i = 0; i < animalCount; i++){
    animals[i].setFound(false);
  }
  //sets counter to zero
  counter = 0;
  isDone = false;
  
  //writes to serial lcd
  Serial.println("SYSTEM RESET");
  writeToLCD("SYSTEM RESET");
  delay(3000);
  writeToLCD(("Counter set to " + String(counter)).c_str());
  delay(3000);
  systemReady();
}

void writeToLCD(String str){
    // move cursor to beginning of first line
  LCD.write(254); 
  LCD.write(128);

  // clear display by sending spaces
  LCD.write("                "); 
  LCD.write("                ");

  LCD.write(str.c_str());
}


void systemReady(){
  writeToLCD("System ready     scan now");
}

String readRFID(void){
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  byte uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 40);
  String input = String(uid[0], HEX) + String(uid[1], HEX) + String(uid[2],HEX) + String(uid[3],HEX);
  return input;
}

bool SetupRFIDShield(void){
  nfc.begin(); 
  if (!nfc.getFirmwareVersion()){
    return false;
  }  
  nfc.SAMConfig();
  return true;
}
