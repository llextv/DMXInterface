# DMX Interface — ArtNet to DMX Converter

A DIY Ethernet-to-DMX interface designed to convert **Art-Net DMX data into physical DMX512 outputs**.

The goal of this project is to create an affordable alternative to commercial Art-Net to DMX interfaces while keeping the hardware simple, easy to assemble and fully customizable.

---

# Overview

## What does this project do?

This interface acts as a bridge between an Ethernet network and DMX lighting equipment.

Instead of connecting a lighting controller directly to a DMX cable, the controller sends DMX data over an Ethernet network using the **Art-Net protocol**.

This makes the interface particularly useful for **DMX lighting, stage lighting, DJ setups, architectural lighting and other Art-Net compatible applications**.

---

# Hardware

The complete Bill of Materials is available in:

[BOM.csv](BOM.csv)

The detailed BOM is also available at the end of this document.

---

# Mechanical Design

The enclosure was designed to be **fully 3D printable**.

The objective was to avoid requiring specialized machining or industrial manufacturing equipment.

The enclosure can therefore be reproduced using a standard FDM 3D printer.

## Case

![DMX Interface enclosure](Pictures/image-2.png)

![DMX Interface enclosure](Pictures/image-3.png)

![DMX Interface enclosure](Pictures/image-4.png)

---

# CAD Files

The CAD files are provided in STEP format so that the enclosure can be modified using most modern CAD software.

![DMX Interface enclosure](Pictures/assf.png)

* [Bottom DMX Interface](cad/BottomDMXInterface.step)
* [DMX Interface Enclosure](cad/DMXInterface.step)
* [Assembly](cad/AssemblageDMXInterface.step)

---

# Electronic Design

## Schematic

![DMX Interface schematic](Pictures/scheme2.png)

The electronics are divided into three main sections:

---

# Firmware

The firmware is responsible for converting Art-Net packets into DMX data.

The current implementation uses an ESP32 together with the following libraries:

* `Ethernet_Generic`
* `ArtnetWifi`
* `ESP32DMX`

---

# Firmware Configuration

The firmware currently uses a static IP address:

```cpp
IPAddress ip(192, 168, 1, 50);
```

This can be changed to match the network used for the lighting setup.

The W5500 chip select pin is configured as:

```cpp
#define W5500_CS 10
```

The four DMX transmit pins are:

```cpp
#define DMX1_TX 4
#define DMX2_TX 5
#define DMX3_TX 6
#define DMX4_TX 7
```

These values must match the actual wiring of the ESP32.

---

# Main Firmware

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

void onDmxFrame(
  uint16_t universe,
  uint16_t length,
  uint8_t sequence,
  uint8_t* data
) {
  switch (universe) {
    case 0:
      memcpy(universe0, data, length);

      for (int i = 0; i < length; i++)
        dmx1.write(i + 1, data[i]);

      break;

    case 1:
      memcpy(universe1, data, length);

      for (int i = 0; i < length; i++)
        dmx2.write(i + 1, data[i]);

      break;

    case 2:
      memcpy(universe2, data, length);

      for (int i = 0; i < length; i++)
        dmx3.write(i + 1, data[i]);

      break;

    case 3:
      memcpy(universe3, data, length);

      for (int i = 0; i < length; i++)
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

---

# BOM

| Category      | Item                                   | Quantity | Unit Price (€) |   Total (€) | Notes                  |
| ------------- | -------------------------------------- | -------: | -------------: | ----------: | ---------------------- |
| Communication | W5500                                  |        1 |           3.89 |        3.89 | Ethernet controller    |
| Communication | MAX3485 Module RS-485                  |        4 |           1.40 |        5.60 | One per DMX output     |
| Controls      | ESP-WROOM-32                           |        1 |           5.89 |        5.89 | Main controller        |
| Connectique   | XLR 3Pin Panel Mount Connectors Female |        4 |           1.05 |        4.19 | Lot of 4 connectors    |
| Power         | 5V 2A Power Supply                     |        1 |           2.99 |        2.99 | Main power supply      |
| Prototype     | 12 Holes Bridge                        |        2 |           2.37 |        4.74 | Electrical connections |
| **TOTAL**     |                                        |          |                | **27.30 €** |                        |

---