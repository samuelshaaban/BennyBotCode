#pragma once
#include "filesystem.h"

enum Bot {A, B};


// modifiable configuration read from file
class Config {
  public:
  void read(Filesystem&);

  Bot get_bot();

  int get_key_period();
  int get_bat_period();
  int get_control_period();

  double get_min_bat();
  double get_low_bat();

  // more functions to read specific attributes of our config


  private:
  Bot bot;
  // more configuration items read from file
};