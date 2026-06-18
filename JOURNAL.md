---
title: "DMXInterface"
author: "llextv"
description: "An interface between Ethernet --> DMX (ArtNet to DMX)"
created_at: "2026-06-17"
---

# June 17: Defining system & BOM test
I would like to create a system base on ESP with two main component:
-> DMX Interface
-> Ethernet Interface

![alt text](image.png)

Management of 4 universe is good so we need 4 DMX interface and software for distribute DMX to good interface

This Interface need to be compaptible with QLC+ for DMX Management with ArtNet difusion on 4 universe.

I've work on my BOM with all documentation, choice of ESP32-S3 to management better and efficency 4 universe.

**Preview BOM:**
-> W5500 (https://fr.aliexpress.com/item/1005009353017777.html) = 3,89€
-> 4 * MAX485 Module RS-485 (https://fr.aliexpress.com/item/1005007011742123.html) = 0.83€ * 4 = 3,32€
-> ESP32-S3 (https://fr.aliexpress.com/item/1005012092039320.html) = 5.69€
-> 4 * XLR 3Pin Panel Mount Connectors Female (https://fr.aliexpress.com/item/1005008919369057.html) = 4.19€
-> 5V 2A Alimentation (https://fr.aliexpress.com/item/1005005539475429.html) = 2.99€
-> 2 * 12 Holes Bridge (https://fr.aliexpress.com/item/1005001742109041.html) = 2 * 1,37€ = 4,74€

I will made a little box in PLA with my 3D Printer for put all component but no PCB needed for this project, I have cable at home for this project.

**Total time spent: 3 hours**

# June 18: Electric scheme
I made electrical scheme with all component:
![alt text](image-1.png)

For a total of 24,82€ arround $28,55

One of my actual question is on Alimentation (Jack at the base) but I will try to cut the cable and sort +5V and GND cable from this

I spend lot of time in my scheme (ChatGPT fail for response me with the PIN of W5500 and no technical docs ?)

**Total time spent: 2 hours**