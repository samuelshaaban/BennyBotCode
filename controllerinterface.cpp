#include "controllerinterface.h"

ControllerInterface::ControllerInterface(ControllerType type) {
  if(type == XBOX_ONE) {
    // setup xbox one
  }
}

void ControllerInterface::setup() {}
Keys ControllerInterface::read() {}
void ControllerInterface::set_battery(double volts) {}