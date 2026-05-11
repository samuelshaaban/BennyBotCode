#include "util.h"
#include <Arduino.h>
#include "SD.h"
#include <SPI.h>

void fs_setup() {
  if(!SD.begin()) {
    Serial.println("Card Mount Failed");
    return;
  }

  uint8_t card_type = SD.cardType();
  if(card_type == CARD_NONE) {
    Serial.println("No SD Card attached");
    return;
  }

  Serial.println("SD Card attached successfuly, Size: " + String(SD.cardSize() >> 20));
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