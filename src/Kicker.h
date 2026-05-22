#pragma once
#include <Arduino.h>
#include "global.h"
#include "readController.h"

extern unsigned long LastKickedTime;
enum class Kicker { Charge, CanUse, Kicking };


void Kicker_Setup();
void Kick();
void Kicker_end();

extern unsigned long LastKickedTime;
extern bool KickerCharge;
extern uint CoolTime;