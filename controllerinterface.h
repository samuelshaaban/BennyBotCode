#pragma once
#include <Bluepad32.h>

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
  double drive_x, drive_y; // drive motors - 1 stick
  double aux1, aux2, aux3, aux4; // mappable remaining analog inputs

  unsigned int motor_cmd; // number to run an auxiliary motor routine
  unsigned int media_cmd; // probably enumerate configured files to play and just send a number to media, 0 = nothing

  // maybe some other cmd to control gauges or something
};

// then each controllable module reads config to map aux analog and cmds to specific behavior


class ControllerInterface {
  public:
  ControllerInterface(ControllerType);
  void setup();
  void set_battery(double);

  Keys read(); // or we could store keys privately, and add various functions to read different things

  /*
  as an alternative to the keys struct, we could make a few different functions

  struct Pair { double x, y; }; 
  Pair get_drive();
  Pair get_aux_stick();
  double get_trigger(int num); // unsigned values unlike stick

  and maybe have cmds retrieved from a queue, but probably best to separate to destinations here so multiple different modules can pop from same Controller object easily
  unsigned int get_motor_cmd(); // pop and return first element of queue
  unsigned int get_media_cmd();
  unsigned int get_other_cmd();

  private:
  Queue motor_cmds, media_cmds;
  */
};