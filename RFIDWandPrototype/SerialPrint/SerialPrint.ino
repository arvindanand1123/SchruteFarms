#include <Adafruit_PN532.h>
Adafruit_PN532 nfc(2,3);

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
    
  if (success) 
  {
      Serial.print(uid[0],HEX);//...
      Serial.print(uid[1],HEX);//...
      Serial.print(uid[2],HEX);//...
      Serial.print(uid[3],HEX);//.
      Serial.println("");
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
