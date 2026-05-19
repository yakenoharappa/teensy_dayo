#pragma once
#include <Arduino.h>
#include "Serial.h"

class readingSerial
{
private:
    /* data */
public:
    int SerialNumber;
    uint8_t Start;
    uint8_t End;
    int amountData;

    readingSerial(int number, uint8_t StartC, uint8_t endC, int amount);
    void readData();
};

