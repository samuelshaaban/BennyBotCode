#include <Arduino.h>
#include <Bluepad32.h>
#include "util.h"
#include "config.h"
#include "controllerinterface.h"
#include "motors.h"
#include "servos.h"
#include "gpio.h"
#include "antitheft.h"
#include "media.h"

Config config;

//ControllerInterface controller(XBOX_ONE);
ControllerPtr myController; // part of non-class controller implementation
Motors motors;
Servos servos;

Gpio gpio;
Antitheft antitheft;
Media media;
//USB usb

unsigned long now, last_key, last_bat, last_control;


// START  copied code from controller arduino sketch
// This callback gets called any time a new gamepad is connected.
void onConnectedController(ControllerPtr ctl) {
    // if no controller is connected, connect controller
    if (myController == nullptr) {
        Serial.print("CALLBACK: Controller is connected");
        // Additionally, you can get certain gamepad properties like:
        // Model, VID, PID, BTAddr, flags, etc.
        ControllerProperties properties = ctl->getProperties();
        Serial.printf("Controller model: %s, VID=0x%04x, PID=0x%04x\n", ctl->getModelName().c_str(), properties.vendor_id,
                       properties.product_id);
        myController = ctl;
    } else {
        Serial.println("CALLBACK: Controller connected, but could not finnd empty slot");
    }
}
// " disconnected
void onDisconnectedController(ControllerPtr ctl) {
    if (myController == ctl) {
        Serial.print("CALLBACK: Controller disconnected.");
        myController = nullptr;
    } else {
        Serial.println("CALLBACK: Controller disconnected, but not found in myControllers");
    }
}
void dumpGamepad(ControllerPtr ctl) {
    Serial.printf(
        "idx=%d, dpad: 0x%02x, buttons: 0x%04x, axis L: %4d, %4d, axis R: %4d, %4d, brake: %4d, throttle: %4d, "
        "misc: 0x%02x, gyro x:%6d y:%6d z:%6d, accel x:%6d y:%6d z:%6d\n",
        ctl->index(),        // Controller Index
        ctl->dpad(),         // D-pad
        ctl->buttons(),      // bitmask of pressed buttons
        ctl->axisX(),        // (-511 - 512) left X Axis
        ctl->axisY(),        // (-511 - 512) left Y axis
        ctl->axisRX(),       // (-511 - 512) right X axis
        ctl->axisRY(),       // (-511 - 512) right Y axis
        ctl->brake(),        // (0 - 1023): brake button
        ctl->throttle(),     // (0 - 1023): throttle (AKA gas) button
        ctl->miscButtons(),  // bitmask of pressed "misc" buttons
        ctl->gyroX(),        // Gyro X
        ctl->gyroY(),        // Gyro Y
        ctl->gyroZ(),        // Gyro Z
        ctl->accelX(),       // Accelerometer X
        ctl->accelY(),       // Accelerometer Y
        ctl->accelZ()        // Accelerometer Z
    );
}
void processGamepad(ControllerPtr ctl) {
    // There are different ways to query whether a button is pressed.
    // By query each button individually:
    //  a(), b(), x(), y(), l1(), etc...

    if (ctl->x()) {
        // Some gamepads like DS3, DS4, DualSense, Switch, Xbox One S, Stadia support rumble.
        // It is possible to set it by calling:
        // Some controllers have two motors: "strong motor", "weak motor".
        // It is possible to control them independently.
        ctl->playDualRumble(0 /* delayedStartMs */, 250 /* durationMs */, 0x80 /* weakMagnitude */,
                            0x40 /* strongMagnitude */);
    }

    // Another way to query controller data is by getting the buttons() function.
    // See how the different "dump*" functions dump the Controller info.
    dumpGamepad(ctl);
}
void processControllers() {
        // M: check only controllers that are connected and have new data
    if (myController && myController->isConnected() && myController->hasData()) {
        if (myController->isGamepad()) {
            processGamepad(myController);
        } else {
            Serial.println("Unsupported controller");
        }
    }
}
// END copied code from arduino sketch

void setup() {
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Begin!");

  fs_setup();
  config.read();

  //controller.setup();
  Serial.printf("Firmware: %s\n", BP32.firmwareVersion());
  const uint8_t* addr = BP32.localBdAddress();
  Serial.printf("BD Addr: %2X:%2X:%2X:%2X:%2X:%2X\n", addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]);
  BP32.setup(&onConnectedController, &onDisconnectedController); // Setup the Bluepad32 callbacks

  motors.setup(config);
  servos.setup(config);

  gpio.setup(config);
  media.setup(config);
  antitheft.setup(config);

  now = last_key = last_bat = last_control = millis();
  Serial.println("Setup complete")
}


void loop() {
  now = millis();

  if (now > last_key + config.get_key_period()) {
    Serial.println("Checking key");
    while (!gpio.read_key_switch()) {
      Serial.println("Antitheft system armed");
      // sleep, wake up occasionally to check lidar
      // not sure what the best way to sleep is, loop is inefficient, light sleep will drop bluetooth though
      if (antitheft.theft_detected()) media.trigger_alarm();
    }  // key turned back on
    media.reset_alarm();
  }

  if (now > last_bat + config.get_bat_period()) {
    Serial.println("Checking battery");
    // read battery, pass to controller class for rumble spacing
    // as battery nears min, decrease rumble spacing
    // constant rumble just before powering system down

    double bat = gpio.read_battery();
    //controller.set_battery(bat);

    if (bat < config.get_min_bat()) {
      Serial.println("Battery below minimum");
      // shutdown
      // we don't have a shutdown switch or way to shut off ESP32
      // best to turn off all peripherals, enter deep sleep
    }
  }

  if (now > last_control + config.get_control_period()) {
    Serial.println("Checking controller");
    
    /*
    Keys keys = controller.read();
    motors.send_keys(keys);
    servos.send_keys(keys);
    media.send_keys(keys);
    */

    bool dataUpdated = BP32.update();
    if (dataUpdated) processControllers();
  }

}
