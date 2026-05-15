#include "Kicker.h"

unsigned long LastKickedTime = millis();
bool KickerCharge = 0;
uint CoolTime = 30;


void Kicker_Setup(){
    pinMode(FET1, OUTPUT);
    pinMode(FET2, OUTPUT);
    LastKickedTime = millis();
}

void Kick(){
    
    if (digitalRead(FET2) == HIGH)
    {
        digitalWrite(FET2, LOW);
    }
    
    if ( (millis() - LastKickedTime) > CoolTime && KickerCharge == 1 )
    {
        digitalWrite(FET2, HIGH);
        digitalWrite(FET1, LOW);
        LastKickedTime = millis();
        KickerCharge = 0;
    }
    else if ( (millis() - LastKickedTime) <= CoolTime ){
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, HIGH);
        KickerCharge = 0;
    }
    else{                                   // >Cooltimeで、Kicker == 0
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, HIGH);
        KickerCharge = 1;
    }
    

    if (digitalRead(FET2) == HIGH)
    {
        digitalWrite(FET2, LOW);
    }
}