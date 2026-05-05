#pragma once
#include "config.h"
#include "controller.h" // Keys

class Media {
  public:
  Media();
  void setup(Config&, Filesystem&);
  void send_keys(Keys&); // not completely sure how these should be interpreted yet

  void trigger_alarm();
  void reset_alarm();
};