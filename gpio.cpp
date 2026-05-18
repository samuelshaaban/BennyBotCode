#include "gpio.h"
#include "pins.h"
#include <Arduino.h>

void Gpio::setup() {
  Serial.println("Setting up GPIO pins");
  pinMode(pins::gauge1, OUTPUT);
  pinMode(pins::gauge2, OUTPUT);
  pinMode(pins::key, INPUT_PULLUP);
  pinMode(pins::battery, INPUT);
  Serial.println("GPIO setup complete");
}


void Gpio::write_gauge(int gauge, double val) {
  int d = val / 10 * (1<<12); // scale 10V to 12 bit DAC
  if(gauge == 1)      analogWrite(pins::gauge1, d);
  else if(gauge == 2) analogWrite(pins::gauge2, d);
  else Serial.printf("Gpio::write_gauge: invalid gauge number: %d, ignoring\n", gauge);
}

bool Gpio::read_key_switch() { return !digitalRead(pins::key); } // on = gnd, inverted output
double Gpio::read_battery() {
  // convert 12 bit int to 3.3V float, then unscale 220/(220+1000) = 11/61 voltage divider
  return (double)analogRead(pins::battery) / (1<<12) * 3.3 * 61 / 11;
}
