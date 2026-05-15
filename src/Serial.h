#pragma once
#include <Arduino.h>

static HardwareSerial *Serials[] = { NULL, &Serial1, &Serial2, &Serial3, &Serial4, &Serial5, &Serial6, &Serial7};
const int MOTORSerial = 1;
const int ControllerSerial = 2;