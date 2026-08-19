# DMX Interface — ArtNet to DMX Converter

A DIY Ethernet-to-DMX interface designed to convert **ArtNet signals into DMX output**.

This project provides a compact, low-cost and reproducible solution capable of controlling **4 independent DMX universes** through an Ethernet connection.

---

# Overview

## Features

- Fully 3D printable enclosure
- Low-cost and easily reproducible design
- Ethernet input using ArtNet protocol
- 4 independent DMX output universes
- Standard DMX XLR outputs
- Open-source hardware and software

---

# Hardware

The complete Bill of Materials is available in:

[BOM.csv](BOM.csv)

A detailed BOM is also available at the end of this document.

---

# Mechanical Design

The enclosure was designed to be fully 3D printable, allowing easy reproduction and customization.

## Case

![DMX Interface enclosure](Pictures/image-2.png)

![DMX Interface enclosure](Pictures/image-3.png)

![DMX Interface enclosure](Pictures/image-4.png)

## CAD Files
![DMX Interface enclosure](Pictures/assf.png)
- [Bottom DMX Interface](cad/BottomDMXInterface.step)
- [DMX Interface Enclosure](cad/DMXInterface.step)
- [Assembly](cad/AssemblageDMXInterface.step)
---

# Electronic Design

## Schematic

![DMX Interface schematic](Pictures/scheme2.png)

---

# Firmware

The interface is based on an ESP32 and provides conversion between ArtNet and DMX protocols.

Main features:

- Ethernet communication through a W5500 module
- ArtNet protocol support
- Four independent DMX output channels
- RS-485 communication using MAX485 modules

The firmware receives ArtNet DMX packets and forwards each universe to its corresponding DMX output.

## Main Script

```c
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
```
## BOM
| Catégorie | Article | Quantité | Prix unitaire (€) | Prix total (€) | Notes | URL |
|---|---|---:|---:|---:|---|---|
| Communication | W5500 | 1 | 3,89 | 3,89 | | https://fr.aliexpress.com/item/1005009353017777.html |
| Communication | MAX3485 Module RS-485 | 4 | 1,40 | 5,60 | | https://fr.aliexpress.com/item/1005006007545162.html |
| Controls | ESP-WROOM-32 | 1 | 5,89 | 5,89 | | https://fr.aliexpress.com/item/1005012697513614.html |
| Connectique | XLR 3Pin Panel Mount Connectors Female | 4 | 1,05 | 4,19 | Lot de 4 connecteurs | https://fr.aliexpress.com/item/1005008919369057.html |
| Power | Alimentation 5V 2A | 1 | 2,99 | 2,99 | | https://fr.aliexpress.com/item/1005005539475429.html |
| Prototype | 12 Holes Bridge | 2 | 2,37 | 4,74 | | https://fr.aliexpress.com/item/1005001742109041.html |
| **TOTAL** | | | | **27,30 €** | | |
