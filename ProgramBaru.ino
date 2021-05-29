
#include <WiFi.h>

/////// inisialisasi TELEGRAM 
#include "CTBot.h"
 
CTBot myBot;
String ssid  = "test1";
String pass  = "putra146";
String token = "1693110941:AAFP39dwBKnBTRaMStq0whewAJFq1bsddYU";

char Data;

//#define relay D5
#define buzz 4
//#define sensor D7

//////// inisialisasi LORA 
#include <SPI.h>
#include <LoRa.h>

const int ss = 5;
const int rst = 14;
const int dio0 = 2;

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
}

void loop(){

   int packetSize = LoRa.parsePacket();
   TBMessage msg; 
        if (packetSize) 
         {
          // received a packet
          Serial.print("Received packet '");
          // read packet
           while (LoRa.available()) 
           {
            Data =((char) LoRa.read());
            Serial.print(Data);
           }
                   
                    if (myBot.getNewMessage(msg))
                    {
                      if (msg.text.equalsIgnoreCase("/cek_kondisi_tambak"))
                      {
                        
                        Serial.println("Mengirim pesan ke Telegram...");
                              
                              if (Data == '1') {
                            String welcome = "Kondisi Air Pada Tambak Saat ini TINGGI (Tercukupi Air).\n";
                            myBot.sendMessage(msg.group.id, welcome);
                            }
                          else if (Data== '2') {
                            String welcome = "Kondisi Air Pada Tambak Saat ini SEDANG (Tercukupi Air).\n";
                            myBot.sendMessage(msg.group.id, welcome);
                            }
                          else if (Data == '3') {
                            String welcome = "Kondisi Air Pada Tambak Saat ini RENDAH (Kekurangan Air).\n PINTU AIR TERBUKA.\n";
                            myBot.sendMessage(msg.group.id, welcome);
                            digitalWrite (buzz,HIGH);
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
         }
}
                          
