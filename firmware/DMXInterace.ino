#include <SPI.h>
#include <Ethernet_Generic.h>
#include <ArtnetWifi.h>
#include <ESP32DMX.h>

#define W5500_CS 10

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x01
};

IPAddress ip(192, 168, 1, 50);

#define DMX1_TX 4
#define DMX2_TX 5
#define DMX3_TX 6
#define DMX4_TX 7

ESP32DMX dmx1;
ESP32DMX dmx2;
ESP32DMX dmx3;
ESP32DMX dmx4;

uint8_t universe0[512];
uint8_t universe1[512];
uint8_t universe2[512];
uint8_t universe3[512];

ArtnetWifi artnet;


void onDmxFrame(uint16_t universe, uint16_t length, uint8_t sequence, uint8_t* data){
  switch (universe)
  {
    case 0:
      memcpy(universe0, data, length);
      for(int i=0;i<length;i++)
        dmx1.write(i + 1, data[i]);
      break;
    case 1:
      memcpy(universe1, data, length);
      for(int i=0;i<length;i++)
        dmx2.write(i + 1, data[i]);
      break;
    case 2:
      memcpy(universe2, data, length);
      for(int i=0;i<length;i++)
        dmx3.write(i + 1, data[i]);
      break;
    case 3:
      memcpy(universe3, data, length);
      for(int i=0;i<length;i++)
        dmx4.write(i + 1, data[i]);
      break;
  }
}

void setup()
{
  Serial.begin(115200);
  Serial.println("DMX Interface Starting");
  Ethernet.init(W5500_CS);
  Ethernet.begin(mac, ip);
  Serial.print("IP: ");
  Serial.println(Ethernet.localIP());
  dmx1.init(DMX1_TX);
  dmx2.init(DMX2_TX);
  dmx3.init(DMX3_TX);
  dmx4.init(DMX4_TX);
  artnet.begin();
  artnet.setArtDmxCallback(onDmxFrame);
  Serial.println("ArtNet Ready");
}

void loop()
{
  artnet.read();
}