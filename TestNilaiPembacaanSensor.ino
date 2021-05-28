

#include <SPI.h>
#include <LoRa.h>
char data1 = '1';
char data2 = '2';
char data3 = '3';

String LoRaMessage = "";

int buzz = 3;

void setup () {
  pinMode (buzz,OUTPUT);
  Serial.begin (9600);
  while (!Serial);
  Serial.println("LoRa Sender");

  if (!LoRa.begin(433E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
void loop() {
  // read the input on analog pin 0:
  int data = analogRead(A2);
  Serial.println(data);
  if (data > 420) {
    //data = 100;
    Serial.println("kirim data");
    Serial.println(data1);
      LoRa.beginPacket();
      LoRa.print(data1);
      LoRa.endPacket();
      delay(1000);
    Serial.println("PENUH");
    digitalWrite (buzz,LOW);
    }
  if ((data > 320) && (data <= 420)) {
    //data = 50;
    Serial.println("kirim data");
    Serial.println(data2);
    LoRa.beginPacket();
    LoRa.print(data2);
    LoRa.endPacket();
    delay(1000);
    Serial.println("SEDANG");
    digitalWrite (buzz,LOW);
    }
  if(data <= 330){
    //data = 0;
    Serial.println("kirim data");
    Serial.println(data3);
    LoRa.beginPacket();
    LoRa.print(data3);
    LoRa.endPacket();
      delay(1000);
    Serial.println("Kurang");
    digitalWrite (buzz,HIGH);
    delay(500);
  }
  
//  LoRaMessage = String(data);
// 
//  // send packet
//  LoRa.beginPacket();
//  LoRa.print(LoRaMessage);
//  LoRa.endPacket();
//  delay(1000);
  }
