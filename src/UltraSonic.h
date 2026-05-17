#pragma once
#include <Arduino.h>

class UltraSonic
{

public:

    static const int amount = 4;
    const int pin[amount] = {5, 6, 7, 8};
    float value[amount];

};

extern UltraSonic MyUSonic;
//const int UltraSonicPIN[HowManyUltraSonic] = {5, 6, 7, 8};




class UltraSonic1
{
public:
    int trig_pin;
    int echo_pin;
    UltraSonic1(int _trig_pin, int _echo_pin);
    float value;

};

extern UltraSonic MyUSonic;
//const int UltraSonicPIN[HowManyUltraSonic] = {5, 6, 7, 8};

