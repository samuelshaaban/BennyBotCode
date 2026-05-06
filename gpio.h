#pragma once
#include "config.h"

// holds key and battery monitor and gauges
class Gpio {
  public:
  Gpio();
  void setup(Config&);
  
  void write_gauge(int, double);
  bool read_key_switch();
  double read_battery();
};