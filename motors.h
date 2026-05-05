#pragma once
#include "config.h"
#include "controller.h" // Keys

class Motors {
  public:
  Motors();
  void setup(Config&);
  void send_keys(Keys&);
};