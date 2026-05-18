#include "UltraSonic.h"

UltraSonic MyUSonic;

UltraSonic1::UltraSonic1(int _trig_pin, int _echo_pin){
    trig_pin = _trig_pin;
    echo_pin = _echo_pin;
    pinMode(trig_pin, OUTPUT);
    pinMode(echo_pin, INPUT);

}



void USonic_Setup(){

}



void USonic_Update(){

}