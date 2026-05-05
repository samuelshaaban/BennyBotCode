#include "config.h"

#define KEY_PERIOD 100 // ms
#define BAT_PERIOD 100 // ms
#define CONTROL_PERIOD 100 // ms

Config::Config() {}
void Config::read(Filesystem &fs) {}
Bot Config::get_bot() {}
int Config::get_key_period() {return KEY_PERIOD;}
int Config::get_bat_period() {return BAT_PERIOD;}
int Config::get_control_period() {return CONTROL_PERIOD;}
double Config::get_min_bat() {}
double Config::get_low_bat() {}
