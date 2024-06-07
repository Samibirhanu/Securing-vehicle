#include <MFRC522.h>
#include <SPI.h>

#define SAD 10
#define RST 5

MFRC522 nfc(SAD, RST);

void setup() {
  SPI.begin();
  Serial.begin(115200);
  nfc.begin();
  pinMode(2, OUTPUT);
  pinMode(3,OUTPUT);

  byte version = nfc.getFirmwareVersion();
  if (!version) {
    Serial.print("Didn't find MFRC522 board.");
    while(1); //halt
  }

}

byte samuelTag[5] = {0x33, 0x8B, 0x91, 0xFC};

void loop() {
  byte status;
  byte data[MAX_LEN];
  byte serial[5];

  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);

    nfc.selectTag(serial);

    if (memcmp(serial, samuelTag, 4) == 0) {
      Serial.println("Tag verified as Samuel's RFID.");
      digitalWrite(2,HIGH);
      delay(100);
      digitalWrite(2,LOW);
    } else {
      Serial.println("Unknown RFID.");
      digitalWrite(3,HIGH);
      delay(100);
      digitalWrite(3,LOW);
    }

    nfc.haltTag();
  }
  delay(2000);
}
