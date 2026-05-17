#include "motor_convert.h"


MotorDriver Motors;

void motor_convert::MotorDeg(int motor1, int motor2, int motor3, int motor4){
    int motors[5] = {0, motor1, motor2, motor3, motor4};
    for (int i = 1 ; i <= 4 ; i++ )
    {
        motor_convert::MotorDegs[i] = motors[i];
    }
}

void motor_convert::MotorPersents(int deg){
    for (int i = 1; i <= 4; i++)
    {
        motor_convert::Mvalues[i] = sin(deg_radian(motor_convert::MotorDegs[i] - deg)) * MotorSpeed;
    }

    Motors.UsedDriver = 0;
    Motors.move(Mvalues[1], Mvalues[2], Mvalues[3], Mvalues[4]);
    
}


void motor_convert::stoping(){
    Motors.stop();
    
}