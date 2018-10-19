#include <Adafruit_PN532.h>
#include <iostream>
Adafruit_PN532 nfc(2,3);
void setup() {
  Serial.begin(9600);
  if(!SetupRFIDShield()){
    Serial.print("Error: RFID not found");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
class Animal{
  String loc;
  String hex;
  void setHex(String s){
    hex = s;
  }
  String getHex(void){
    return hex;
  }
  void setLoc(String s){loc = s;}
  void getLoc(void){return loc;}
  
};

bool SetupRFIDShield(void){
  nfc.begin(); 
  if (!nfc.getFirmwareVersion()){
    return false;
  }  
  nfc.SAMConfig();
  return true;
}
