#pragma once

#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_BNO055.h>

extern Adafruit_BNO055 bno; //I2Cのアドレス定義

extern float yaw_BNO;
extern double theta;
extern int DAC_port;
