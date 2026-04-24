#include <Arduino.h>
#include <ESP32Servo.h>

FileSystem fs;
Config config;

Controller controller(XBOX_ONE);
Motors motors;
Servos servos;

GPIO gpio; // holds key and battery monitor and gauges
Lidar lidar;
Media media;
//USB usb

unsigned long now, last_key, last_bat, last_control;

void setup() {
  Serial.begin(115200);

  fs.setup(config.pins);
  config.read(fs.read_config());

  controller.setup();
  motors.setup(config);
  servos.setup(config);

  lidar.setup(config);
  gpio.setup(config);
  media.setup(config, fs);

  now = last_key = last_battery = last_controller = millis();
}


void loop() {
  now = millis();

  if(now > last_key + KEY_PERIOD) 
    while(!gpio.get_key()) {
      // sleep, wake up occasionally to check lidar
    }
  }

  if(now > last_bat + BAT_PERIOD) {
    // read battery, pass to controller class for rumble spacing
    // as battery nears min, decrease rumble spacing
    // constant rumble just before powering system down

    int bat = gpio.read_bat();
    controller.set_bat(bat);

    if(bat < MIN_BAT) {
      // shutdown
    }
  }

  if(now > last_control + CONTROL_PERIOD) {
    Keys keys = controller.read();
    motors.send_keys(keys);
    servos.send_keys(keys);
    gpio.send_keys(keys);
    media.send_keys(keys);
  }
}
