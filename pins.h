#pragma once
// need this separate from config to avoid cyclical includes

struct pins {
  public:
  static constexpr int
    battery = 4, 
    key = 6,
    siren = 5, // inverted

    motor1 = 48,
    motor2 = 47,
    motor3 = 45,
    motor4 = 21,
    motor_switch = 24,

    actuator1 = 16,
    actuator2 = 18,

    servo_sda = 15,
    servo_scl = 17,
    servo_oe = 8,

    sd_cs = 11,
    sd_sclk = 14,
    sd_mosi = 13,
    sd_miso = 12,
    sd_det = 10,

    lidar_ready = 9,
    lidar_sda = 3,
    lidar_scl = 46,

    gauge1 = 20,
    gauge2 = 19,

    dac_wsel = 7,
    dac_din = 16,
    dac_bck = 18,

    display_A = 43,
    display_B = 44,
    display_C = 2,
    display_D = 40,
    display_r1 = 0,
    display_r2 = 41,
    display_b1 = 38,
    display_b2 = 1,
    display_g1 = 36,
    display_g2 = 42,
    display_clk = 39,
    display_lat = 37,
    display_oe = 35;
};