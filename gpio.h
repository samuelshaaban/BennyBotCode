#pragma once
#include "config.h"

// holds key and battery monitor and gauges
class GPIO {
  public:
  GPIO();
  void setup(Config);
  
  void write_gauge(int num, double val);
  bool read_key_switch();
  double read_battery();
};