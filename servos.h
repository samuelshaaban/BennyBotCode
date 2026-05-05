#pragma once

class Servos {
  public:
  Servos();
  void setup(Config&);
  void send_keys(Keys&);
};