#include "config.h"

#define KEY_PERIOD 5000    // ms
#define BAT_PERIOD 1000    // ms
#define CONTROL_PERIOD 250 // ms

#define MIN_BAT 10   // V
#define LOW_BAT 10.5 // V

Config::Config(): bot(A) {}
void Config::read() {}
Bot Config::get_bot() { return bot; }

int Config::get_key_period() { return KEY_PERIOD;}
int Config::get_bat_period() { return BAT_PERIOD;}
int Config::get_control_period() { return CONTROL_PERIOD;}
double Config::get_min_bat() { return MIN_BAT; }
double Config::get_low_bat() { return LOW_BAT; }
