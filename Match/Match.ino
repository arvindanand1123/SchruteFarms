// Adafruit PN532 - Version: Latest 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
using namespace std;
//Adafruit_PN532 nfc(2, 5, 3, 4);

#define PN532_IRQ   (2)
#define PN532_RESET (3)

Adafruit_PN532 nfc(PN532_IRQ, PN532_RESET);


int counter = 0;
bool isCorrect = false;

class Animal{
  public:
  String loc;
  String hex;
  String type;
  bool isFound = false;
  Animal(String key, String pair, String str){
    setHex(key);
    setLoc(pair);
    setName(str);
  }
  void setHex(String s){hex = s;}
  String getHex(void){return hex;}
  void setLoc(String s){loc = s;}
  String getLoc(void){return loc;}
  void setName(String s){type = s;}
  String getName(void){return type;}
  void setFound(bool isVal){isFound = isVal;}
  bool getFound(void){return isFound;}
};

Animal zebra("d7172b70", "66aca230", "Zebra");
Animal monkey("d25dc356","6691327e", "Monkey");
Animal lion("283c856", "f6566f7e", "Lion");
Animal elephant("12dfc956", "461adf7d", "Elephant");

Animal animals[] = {zebra, monkey, lion, elephant};

void setup() {
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
}

void loop() {
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  byte uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 40);
  String input = String(uid[0], HEX) + String(uid[1], HEX) + String(uid[2],HEX) + String(uid[3],HEX);
  if (success){
    if(input.equals("fbce222d")){reset();}
    isAnimal(input);
    if(isCorrect){
      Serial.println("Board Correct");
    }
  }
}

void isAnimal(String str){
  for(int i = 0; i < 4; i++){
    if(animals[i].getHex().equals(str)){
      //Serial.println(animals[i].getName());
      byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
      byte uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
      bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 40);
      String input = String(uid[0], HEX) + String(uid[1], HEX) + String(uid[2],HEX) + String(uid[3],HEX);
      if(success){
        if(animals[i].getLoc().equals(input) && animals[i].getFound() == false){
          Serial.println("Location Found for " + animals[i].getName());
          animals[i].setFound(true);
          counter++;
        }
      }
    }
  }
  if(counter == 4){
    isCorrect = true;
  }
}

void reset(){
  for(int i = 0; i < 4; i++){
    animals[i].setFound(false);
  }
  isCorrect = false;
  counter = 0;
  Serial.println("RESET");
}



bool SetupRFIDShield(void){
  nfc.begin(); 
  if (!nfc.getFirmwareVersion()){
    return false;
  }  
  nfc.SAMConfig();
  return true;
}
