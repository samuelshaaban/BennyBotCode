#pragma once
#include "config.h"

class Antitheft {
  public:
  Antitheft();
  void setup(Config&);
  bool theft_detected();
};