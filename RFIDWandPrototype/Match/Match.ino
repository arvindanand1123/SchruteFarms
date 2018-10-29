#include <Adafruit_PN532.h>
using namespace std;
Adafruit_PN532 nfc(2,3);

class Animal{
  public:
  String loc;
  String hex;
  String type;
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
};

Animal zebra("d7172b70", "66aca230", "Zebra");
Animal monkey("d25dc356","6691327e", "Monkey");
Animal lion("283c856", "f6566f7e", "Lion");
Animal elephant("12dfc956", "461adf7d", "Elephant");

Animal animals[] = {zebra, monkey, lion, elephant};

void setup() {
  Serial.begin(9600);
  if(!SetupRFIDShield()){
    Serial.print("Error: RFID not found");
  }
}

void loop() {
  byte uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  byte uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  bool success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength, 40);
  String input = String(uid[0], HEX) + String(uid[1], HEX) + String(uid[2],HEX) + String(uid[3],HEX);
  if (success){
    isAnimal(input);
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
      if(animals[i].getLoc().equals(input)){
        Serial.println("Location Found for " + animals[i].getName());
      }
      
    }
  }
}



bool SetupRFIDShield(void){
  nfc.begin(); 
  if (!nfc.getFirmwareVersion()){
    return false;
  }  
  nfc.SAMConfig();
  return true;
}
