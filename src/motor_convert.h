#pragma once

#include <Arduino.h>
#include "global.h"
#include "MotorDriver.h"
#include "Screen.h"

class motor_convert
{
private:
    /* data */
public:
    int MotorDegs[5];
    int Mvalues[5];

    void MotorDeg(int motor1, int motor2, int motor3, int motor4);
    
    void MotorPersents(int deg);

    void stoping();

};



//extern MotorDriver Motors;
