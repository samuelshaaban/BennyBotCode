#pragma once

enum ControllerType {
  XboxOne
};

struct Keys {
// has a variable for every key
};


class Controller {
  public:
  Controller(ControllerType);
  void setup();
  Keys read();
};