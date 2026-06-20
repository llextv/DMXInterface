**DMX Interface**
DIY Interface between Ethernet --> DMX (ArtNet to DMX) work with 4 DMX universe

## Overview
Features:
- 3D printable enclosure
- Low-cost and easily reproducible design
- Ethernet Input (ArtNet)
- 4 DMX Output

## Hardware
See the BOM in [bom.csv](BOM.csv) or at the end of file

## Recap:
**Case:**
![alt text](image-2.png)
![alt text](image-3.png)
![alt text](image-4.png)


**Scheme:**
![alt text](image-1.png)

**Script**
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

**Files**
[Case](assets\DMXInterface.f3d)
[Scheme](assets\DJController.pdn)


## BOM
| Catégorie     | Article                                | Quantité | Prix unitaire (€) | Prix total (€) | Notes                | URL                                                                                                          |
| ------------- | -------------------------------------- | -------: | ----------------: | -------------: | -------------------- | ------------------------------------------------------------------------------------------------------------ |
| Communication | W5500                                  |        1 |              3.89 |           3.89 |                      | [https://fr.aliexpress.com/item/1005009353017777.html](https://fr.aliexpress.com/item/1005009353017777.html) |
| Communication | MAX485 Module RS-485                   |        4 |              0.83 |           3.32 |                      | [https://fr.aliexpress.com/item/1005007011742123.html](https://fr.aliexpress.com/item/1005007011742123.html) |
| Controls      | ESP32-S3                               |        1 |              5.69 |           5.69 |                      | [https://fr.aliexpress.com/item/1005012092039320.html](https://fr.aliexpress.com/item/1005012092039320.html) |
| Connectique   | XLR 3Pin Panel Mount Connectors Female |        4 |              1.05 |           4.19 | Lot de 4 connecteurs | [https://fr.aliexpress.com/item/1005008919369057.html](https://fr.aliexpress.com/item/1005008919369057.html) |
| Power         | Alimentation 5V 2A                     |        1 |              2.99 |           2.99 |                      | [https://fr.aliexpress.com/item/1005005539475429.html](https://fr.aliexpress.com/item/1005005539475429.html) |
| Prototype     | 12 Holes Bridge                        |        2 |              2.37 |           4.74 |                      | [https://fr.aliexpress.com/item/1005001742109041.html](https://fr.aliexpress.com/item/1005001742109041.html) |
| **TOTAL**     |                                        |          |                   |      **24.82** |                      |                                                                                                              |
