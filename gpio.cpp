#include "gpio.h"

Gpio::Gpio() {}
void Gpio::setup(Config &config) {}
void Gpio::write_gauge(int gauge, double val) {}
bool Gpio::read_key_switch() { return true; }
double Gpio::read_battery() { return 0; }
