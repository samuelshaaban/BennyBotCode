#pragma once
#include "config.h"
#include "controllerinterface.h" // Keys

class Motors {
  public:
  Motors();
  void setup(Config&);
  void send_keys(Keys&);
};