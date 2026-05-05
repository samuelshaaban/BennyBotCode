#pragma once
// need this separate from config to avoid cyclical includes

struct pins {
  public:
  static constexpr int
    Lidar_Ready = 9,
    Lidar_SDA = 46;
  // rest of named pins
};