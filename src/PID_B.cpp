#include "PID_B.h"

PID_B::PID_B(bool P, bool I, bool D)
{
    bool Use_P = P;
    bool Use_I = I;
    bool Use_D = D;
    
    int motorW[4] = {1,1,1,1};
}

void PID_B::P(int NowDeg, int Destination, int power)
{
    NowDeg = DegRangeChange(NowDeg, 180);
    Destination = DegRangeChange(Destination, 180);

    PID_B::Difference = NowDeg - Destination;
    PID_B::P_power = PID_B::Difference * power;

}

void PID_B::I(int NowDeg, int Destination, int last_Itime, int power)
{
    PID_B::I_power = (millis() - last_Itime);
}

void PID_B::D(int NowDeg, int Destination)
{

    int NowPast = DegRangeChange(old_deg - NowDeg, 180);
    NowPast = NowPast / ( millis() - last_Dtime );
    old_deg = NowDeg;
    last_Dtime = millis();
}

void PID_B::PIDcombine()
{
    PID_B::P(yaw_BNO, 0, 10/180);
    //PID_B::D()
}
