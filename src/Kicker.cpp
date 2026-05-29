#include "Kicker.h"

unsigned long LastKickedTime = millis();
bool KickerCharge = 0;
uint CoolTime = 2500;


void Kicker_Setup(){
    pinMode(FET1, OUTPUT);
    pinMode(FET2, OUTPUT);
    LastKickedTime = millis();
}

void Kicker(){
    if (Key1.values[Cross] == HIGH && ContollerConnected == true && KickerOnOff == true)
    {
        Kick();
    }
    else if ( (millis() - LastKickedTime) >= 300 )
    {
        Kicker_end();
    } 
}


void Kick(){
    
    /* 
    if (digitalRead(FET2) == HIGH)
    {
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, HIGH);
        digitalWrite(PIN_LED2, LOW);
    } */
    
    if ( (millis() - LastKickedTime) > CoolTime && KickerCharge == 1 )
    {
        digitalWrite(FET2, HIGH);
        digitalWrite(FET1, LOW);
        LastKickedTime = millis();
        KickerCharge = 0;
        digitalWrite(PIN_LED2, HIGH);
        digitalWrite(PIN_LED1, LOW);
    }
    else if ( (millis() - LastKickedTime) <= CoolTime && (millis() - LastKickedTime) >= 300 ){
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, HIGH);
        KickerCharge = 0;
        digitalWrite(PIN_LED2, LOW);
        digitalWrite(PIN_LED1, LOW);
    }
    else if ( (millis() - LastKickedTime) >= 300 ){      // >Cooltimeで、Kicker == 0
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, LOW);
        KickerCharge = 1;
        digitalWrite(PIN_LED2, LOW);
        digitalWrite(PIN_LED1, HIGH);

    }
    

/* 
    if (digitalRead(FET2) == HIGH)
    {
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, HIGH);
        digitalWrite(PIN_LED2, LOW);
    } */
}

void Kicker_end(){
    if ( (millis() - LastKickedTime) >= CoolTime )
    {
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, LOW);
        digitalWrite(PIN_LED2, LOW);
        digitalWrite(PIN_LED1, HIGH);
    }
    else
    {
        digitalWrite(FET2, LOW);
        digitalWrite(FET1, HIGH);
        digitalWrite(PIN_LED2, LOW);
        digitalWrite(PIN_LED1, LOW);
    }

}