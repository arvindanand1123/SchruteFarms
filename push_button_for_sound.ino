#include <Adafruit_VS1053.h>
#include <SPI.h>
#include <SD.h>

#define SHIELD_RESET -1
#define SHIELD_CS     7
#define SHIELD_DCS    6

#define CARDCS 4
#define DREQ   3

Adafruit_VS1053_FilePlayer musicPlayer = 
  Adafruit_VS1053_FilePlayer(SHIELD_RESET, SHIELD_CS, SHIELD_DCS, DREQ, CARDCS);

const int button1Pin = 2;
const int button2Pin = 3;
int button1State;
int button2State;


void setup() {
  Serial.begin(9600);
  Serial.println("Sound Shield Simple Test");
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  //Tests that the shield set up
  if (! musicPlayer.begin()) { 
     Serial.println(F("Couldn't find VS1053, do you have the right pins defined?"));
     while (1);
  }
  Serial.println(F("VS1053 found"));

  //Check to see if the SD card is present
  if (!SD.begin(CARDCS)) {
    Serial.println(F("SD failed, or not present"));
    while (1);  // don't do anything more
  }

//  printDirectory(SD.open("/"), 0);  //lists files

  musicPlayer.setVolume(30,30); //sets volume

  musicPlayer.useInterrupt(VS1053_FILEPLAYER_PIN_INT);

  
}

void loop() {
  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);

  if (button1State == LOW){
    Serial.println(F("Playing Frog"));
    musicPlayer.playFullFile("track002.mp3");
  }

    if (button2State == LOW){
    Serial.println(F("Playing Elephant"));
    musicPlayer.playFullFile("track003.mp3");
  }
}
void printDirectory(File dir, int numTabs) {
   while(true) {
     
     File entry =  dir.openNextFile();
     if (! entry) {
       // no more files
       //Serial.println("**nomorefiles**");
       break;
     }
     for (uint8_t i=0; i<numTabs; i++) {
       Serial.print('\t');
     }
     Serial.print(entry.name());
     if (entry.isDirectory()) {
       Serial.println("/");
       printDirectory(entry, numTabs+1);
     } else {
       // files have sizes, directories do not
       Serial.print("\t\t");
       Serial.println(entry.size(), DEC);
     }
     entry.close();
   }
}
