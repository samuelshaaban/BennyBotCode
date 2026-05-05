#pragma once

enum ControllerType {
  XBOX_ONE
};

struct Keys {
// has a variable for every key
// might rather use the config to map the keys to their function before returning this
};


class Controller {
  public:
  Controller(ControllerType);
  void setup();
  Keys read(); // or we could store keys privately, and add various functions to read different things
  void set_battery(double);
};