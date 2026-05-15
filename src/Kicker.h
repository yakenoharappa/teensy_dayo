#pragma once
#include <Arduino.h>
#include "global.h"

extern unsigned long LastKickedTime;
enum class Kicker { Charge, CanUse, Kicking };


void Kicker_Setup();
void Kick();