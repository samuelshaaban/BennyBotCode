#pragma once
#include "config.h"

// holds key and battery monitor and gauges
class Gpio {
  public:
  void setup();
  
  void write_gauge(int, double);
  bool read_key_switch();
  double read_battery();
};