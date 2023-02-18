#include "LoRa_E220.h"
#define RXD2 16
#define TXD2 17
unsigned long temp;
int cont = 0;

void setup() {

  delay(2000);
  Serial.begin(9600);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
}

void loop() {
  cont = cont + 1;
  String mensg; 
  temp = millis();
  mensg = "A," + String(cont) + " , "+ String(temp);
  Serial2.print(mensg);
  delay(2000);
}
