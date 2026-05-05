#pragma once
#include "config.h"
#include "controller.h" // Keys

class Servos {
  public:
  Servos();
  void setup(Config&);
  void send_keys(Keys&);
};