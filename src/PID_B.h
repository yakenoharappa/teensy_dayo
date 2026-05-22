#pragma once
#include <Arduino.h>

#include "Jyunya.h"
#include "MotorDriver.h"
#include "convert.h"

class PID_B
{
private:
    /* data */
public:
    int Difference;
    float P_power;
    float I_power;
    int last_Dtime;

    int old_deg;

    PID_B(bool P, bool I, bool D);
    void P(int NowDeg, int Destination, int power);
    void I(int NowDeg, int Destination, int last_Itime, int power);
    void D(int NowDeg, int Destination );

    void PIDcombine();
};


