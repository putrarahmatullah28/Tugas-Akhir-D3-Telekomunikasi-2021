
#include <WiFi.h>



/////// inisialisasi TELEGRAM 
#include "CTBot.h"

 
CTBot myBot;
String ssid  = "test1";
String pass  = "putra146";
String token = "1693110941:AAFP39dwBKnBTRaMStq0whewAJFq1bsddYU";

char data;

//#define relay D5
//#define buzz D4
//#define sensor D7

//////// inisialisasi LORA 
#include <SPI.h>
#include <LoRa.h>

const int ss = 5;
const int rst = 14;
const int dio0 = 2;




/////// PROGRAM INTI
void setup()
{
  Serial.begin(9600);
  LoRa.setPins(ss,rst,dio0);
  Serial.println("\nStarting TelegramBot...");
  Serial.print("Menyambungkan ke : ");
  Serial.println(ssid);
  myBot.wifiConnect(ssid, pass);
  myBot.setTelegramToken(token);

  if (myBot.testConnection())
  {
    Serial.print("Terhubung dengan : ");
    Serial.println(ssid);
  }
  else
  {
    Serial.println("\nError.");
  }

//  pinMode(buzz, OUTPUT);
//  digitalWrite(relay, LOW);
//  digitalWrite(buzz, LOW);
}

void loop(){
//  int packetSize = LoRa.parsePacket();
//  if (packetSize) {
//    // received a packet
//    Serial.print("Received packet '");
//
//    // read packet
//    while (LoRa.available()) {
//      char data = LoRa.read();
//      Serial.print(data);
//      if (data == '1'){
//        digitalWrite(buzz, HIGH);   
//        delay(500);
//      }
//    }
// 
//   
//    // print RSSI of packet
//    Serial.print("' with RSSI ");
//    Serial.println(LoRa.packetRssi());
//  }else{
//    digitalWrite(buzz,LOW);
//  }

  // Bagian kontrol Bot Telegram
   TBMessage msg; 
   int packetSize = LoRa.parsePacket();

  if (myBot.getNewMessage(msg))
  {
    if (msg.text.equalsIgnoreCase("/cek_kondisi_tambak"))
    {
      
      Serial.println("Mengirim pesan ke Telegram...");
      
//      String welcome = "Kondisi Tambak Saat ini Tercukupi Air.\n";
//      welcome += "Kondisi Pintu Air : ";
//      boolean a = digitalRead(sensor);
//      Serial.println(a);
//      if (a)welcome += "Terbuka.\n";
//      else welcome += "Tertutup.\n";

     
        if (packetSize) {
          // received a packet
          Serial.print("Received packet '");
      
          // read packet
           while (LoRa.available()) {
            data =((char) LoRa.read());
            Serial.print(data);
            
            if (data == '1') {
          String welcome = "Kondisi Air Pada Tambak Saat ini TINGGI (Tercukupi Air).\n";
          myBot.sendMessage(msg.group.id, welcome);
        // digitalWrite (buzz,HIGH);
          }
        else if (data== '2') {
          String welcome = "Kondisi Air Pada Tambak Saat ini SEDANG (Tercukupi Air).\n";
          myBot.sendMessage(msg.group.id, welcome);
         // digitalWrite (buzz,LOW);
          }
        else if (data == '3') {
          String welcome = "Kondisi Air Pada Tambak Saat ini RENDAH (Kekurangan Air).\n PINTU AIR TERBUKA.\n";
          myBot.sendMessage(msg.group.id, welcome);
//          digitalWrite (buzz,HIGH);
//          delay(500);
//          digitalWrite (buzz,LOW);
//          delay(500);
              }
            }
          }
        }
    else if (msg.text.equalsIgnoreCase("/start"))
    {
      Serial.println("Mengirim pesan ke Telegram...");

      String balasan;
      balasan = (String)"Selamat Datang " + (String) "diBot Monitoring Tambak Ikan" + (String)".\n" +
                (String)"/buka_pintu_air : untuk membuka pintu air pada tambak .\n" +
                (String)"/tutup_pintu_air : untuk menutup pintu air pada tambak.\n" +
                (String)"/cek_kondisi_tambak : mengecek kondisi saat ini.";
      myBot.sendMessage(msg.group.id, balasan);
    }
    else
    {
      Serial.println("Mengirim pesan ke Telegram...");
      String balasan;
      balasan = (String)"Pesan tidak ada!\n" +
                (String)"Silahkan cek kembali dengan\n" +
                (String)"mengirim pesan /start.";
      myBot.sendMessage(msg.group.id, balasan);
    }
  }

/*
  // Bagian Otomatis
  boolean dataSensor = digitalRead(sensor);
  if (dataSensor == 1){
    digitalWrite(relay, HIGH);
  }
  else{
    digitalWrite(relay, LOW);
  }
}
*/
}
