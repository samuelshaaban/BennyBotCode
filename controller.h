#pragma once

enum ControllerType {
  XBOX_ONE
};

/*
need way to control:
drive motors: 2 axis
auxiliary motors/actuators/servos: 1 axis
soundboard / display -> probably enumerate configured files and send just a number to media
volume level?
perhaps change what is on the gauges / display?
*/
struct Keys {
  public:
  double drive_x, drive_y;

  // auxiliary motors, but these depend on configuration so not sure

  unsigned int media_cmd; // probably enumerate configured files to play and just send a number to media, 0 = nothing
  unsigned double volume; // only for A?

  // maybe some other cmd to control gauges or something
};


class Controller {
  public:
  Controller(ControllerType);
  void setup();
  Keys read(); // or we could store keys privately, and add various functions to read different things
  void set_battery(double);
};