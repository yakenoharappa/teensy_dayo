#include "convert.h"

float deg_radian(int deg){
    float radian = deg * M_PI / 180;
    return radian;
}



//radian → deg(度数法)
int radian_deg(float radian){
    int deg = radian * M_PI / 180;
    return deg;
}

//基準方向変換
int changedeg(int value, int change_range){
    value += change_range;
    while (value > 180)
    {
        value -= 360;
    }
    while (value < -180)
    {
        value += 360;
    }
    return value;
}

//角度範囲変換
int DegRangeChange(int before, int which){
    if (which == 360){
        while (before > 360)
        {
            before -= 360;
        }
        while (before < 0)
        {
            before += 360;
        }
    }
    else{
        while (before > 180)
        {
            before -= 360;
        }
        while (before < -180)
        {
            before += 360;
        }
    }
    return before;
}