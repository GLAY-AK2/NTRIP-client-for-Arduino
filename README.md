# NTRIP-client-for-Arduino
DGPS (Differential GPS) and RTK (GPS positioning with centimeter level accuracy) requires the reference position data.

NTRIP caster relays GNSS reference position data Stream from BaseStation (GNSS reference position is called that) to GNSS rover via NTRIP protocol.
NTRIP client get GNSS reference data from NTRIP casters for high precision receivers via Internet.

This suports request Source Table (NTRIP caster has many BaseStation data. Caster informe all of these. Its List is called "Source Table".) and GNSS Reference Data.

## How to use
Please check sample source.

This source has NTRIPClient class based on WiFiClient.
This Developed on ESP32 core for Arduino.

if you want to use Other function, please check WiFiClient.

### Support
Now, this source check with ESP32 & M5Stack.

if you check with other board, please informe me.

And, I'm Japanese. Help me for English.

## Updates
First Commit : Support for ESP32.

2/15 : Compatible with ESP8266. if you can use this, source code needs to include "ESP8266WiFi.h".
       Source code needs to include "WiFi.h" for ESP32.
