#include <Arduino.h>
#include "filesystem.h"
#include "config.h"
#include "controllerinterface.h"
#include "motors.h"
#include "servos.h"
#include "gpio.h"
#include "antitheft.h"
#include "media.h"

Filesystem fs; // probably only used through references stored at setup of media
Config config;

// I don't know why, but the controller code only works if you select
// ESP32-S3-USB-OTG - esp32_bluepad32
// as your board.
// Also need to go to 'Preferences > Additional Board Manager URLS' and paste in:
// https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
ControllerInterface controller(XBOX_ONE);
Motors motors;
Servos servos;

GPIO gpio;
Antitheft antitheft;
Media media;
//USB usb

unsigned long now, last_key, last_bat, last_control;

void setup() {
  Serial.begin(115200);

  fs.setup();
  config.read(fs);

  controller.setup();
  motors.setup(config);
  servos.setup(config);

  gpio.setup(config);
  media.setup(config, fs);
  antitheft.setup(config);

  now = last_key = last_bat = last_control = millis();
}


void loop() {
  now = millis();

  if(now > last_key + config.get_key_period()) {
    while(!gpio.read_key_switch()) {
      // sleep, wake up occasionally to check lidar
      // not sure what the best way to sleep is, loop is inefficient, light sleep will drop bluetooth though
      if(antitheft.theft_detected()) media.trigger_alarm();
    } // key turned back on
    media.reset_alarm();
  }

  if(now > last_bat + config.get_bat_period()) {
    // read battery, pass to controller class for rumble spacing
    // as battery nears min, decrease rumble spacing
    // constant rumble just before powering system down

    double bat = gpio.read_battery();
    controller.set_battery(bat);

    if(bat < config.get_min_bat()) {
      // shutdown
      // we don't have a shutdown switch or way to shut off ESP32
      // best to turn off all peripherals, enter deep sleep
    }
  }

  if(now > last_control + config.get_control_period()) {
    Keys keys = controller.read();
    motors.send_keys(keys);
    servos.send_keys(keys);
    media.send_keys(keys);
  }
}
