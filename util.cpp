#include "util.h"
#include "pins.h"
#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

void print_config() {
  Serial.println("Reading config file:");
  File f = fs_open("/config");
  if(!f) {
    Serial.println("Failed to open /config");
    return;
  }

  while(f.available()) Serial.write(f.read());
  f.close();
  Serial.println();
}

void fs_setup() {
  pinMode(pins::sd_det, INPUT_PULLUP);
  if(digitalRead(pins::sd_det)) { // low means card attached
    Serial.println("No SD Card detected");
    return;
  }
  
  SPI.begin(pins::sd_sclk, pins::sd_miso, pins::sd_mosi, pins::sd_cs);
  if(!SD.begin(pins::sd_cs, SPI, 1000000)) {
    Serial.println("Card Mount Failed");
    return;
  }

  uint8_t card_type = SD.cardType();
  if(card_type == CARD_NONE) {
    Serial.println("No SD Card attached");
    return;
  }

  Serial.println("SD Card attached successfuly, Size: " + String(SD.cardSize() >> 20));
  print_config();
}

File fs_open(const char *name) {
  return SD.open(name);
  // maybe also want to check that its a file, not dir or something unusable
}

/*
For filesystem hierarchy:
- read only default config + documentation
- config
- log dir
- media dir

on setup:
- read and parse config line by line
- any commands that set values (like loop periods or battery thresholds) are written to Config class to override defaults
- array of keybindings stores a list of key combinations + command, which can be:
  - a file with audio or video type - open file during parse and write any errors to log
  - or specific motor routines, mainly for servos
  - any special commands: adjust volume/brightness, anti-theft controls?, ...
*/ 