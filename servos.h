#pragma once
#include "config.h"
#include "controllerinterface.h" // Keys

class Servos {
  public:
  Servos();
  void setup(Config&);
  void send_keys(Keys&);
};