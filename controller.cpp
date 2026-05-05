#include "controller.h"

Controller::Controller(ControllerType type) {
  if(type == XBOX_ONE) {
    // setup xbox one
  }
}

void Controller::setup() {}
Keys Controller::read() {}
void Controller::set_battery(double volts) {}