# BennyBotCode
Arduino software to operate components for both Benny Bots as a part of an engineering capstone project 

# Arduino Setup
## Library Installation
We use a few libraries available for install through the library manager tab of the Arduino IDE.
Install the following libraries:
- Bluepad32 for NINA-W10 boards by Ricardo Quesada
- SD by Arduino, SparkFun

## Custom Board Managers
The Bluepad32 library requires a special ESP32 board manager, separate from
the one from Espressif, in order to properly control the Bluetooth.

First, go to file -> preferences, and paste the following under *Additional boards manager URLs*:
```
https://espressif.github.io/arduino-esp32/package_esp32_index.json
https://raw.githubusercontent.com/ricardoquesada/esp32-arduino-lib-builder/master/bluepad32_files/package_esp32_bluepad32_index.json
```

Then, find the board manager tab on the left, search for *ESP32*, and install the following:
- esp32 by Espressif Systems
- esp32_bluepad32 by Ricardo Quesada

Next, navigate to Tools -> Board -> esp32_bluepad32 and select ESP32-S3-USB-OTG.
(We should confirm that this board doesn't break anything else and more fitting board like ESP32S3 Dev Module doesn't work)

# Needs to handle
## Inputs
- Controller
- Key
- Battery monitor
- Lidar
- SD card filesystem

## Things to control
- Drive motors
- Servos
- Auxiliary motors
  - Launcher (A)
  - Linear actuator (B)
- Audio system (A)
- Display (B)
- Gauges (A)

# Planned control flow
Where do we need threads???

## Setup
- Start filesystem
    - Read configurations
    - Run setups for needed classes

## Loop
- Set multiple different timeouts depending on what it is, key less frequently than controller
- Check key -> transition into sleep mode
- Check battery level -> what are we going to do with this, rumble?
- Poll controller -> Send control signals where they need to go
    - Motors and servos run completely in main loop

### Sleep mode
- Poll antitheft sensors

## Other threads
- Audio and display have another thread running within their class separate from control signals
- Filesystem calls will run on that thread too

## Class architecture
- Config class
    - Can start with predefined config in code
    - Later switch to reading from file
    - Can contain bot specific configurations, which modules to enable
- Controller class
    - Set up to abstract away controller into something we can poll with commands from loop
    - Need this to allow handling of at least 2 different drive motor protocols
- Drive motor class
    - Multiple constructors for different controller types
    - Provides basic movement functions
- Servos class(es)
    - Needs to contain code for every kind of servo usage we plan: head, body movements, merch chute
- Auxiliary motors - linear actuator and launcher
    - Not sure how we want to do this yet
- Audio class
- Display class
- Anti-theft
- Simple GPIO
