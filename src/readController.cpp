#include "readController.h"

bool ContollerConnected = 0;


data dController;
data dGood;
Stick L;
Stick R;
Button Key1;    //Circle,Cross,Triangle,Square,↑↓←→
Button Key2;    //L1~L3,R1~R3



void readController_Setup(){

    Serial.println("Controller_Begin!");
    for (int i = 0; i < 8; i++)
    {
        Key1.Numbers[i] = Keys1[i];
        Key2.Numbers[i] = Keys2[i];
        Key1.Names[i] = Keys1Name[i];
        Key2.Names[i] = Keys2Name[i];
    }
    L.lastStickpower = 0;
    R.lastStickpower = 0;
}

void readController_Update(){
    
    /* 
    Serial1.Checker
    Serial.println(Serial1.read(), BIN);
    Serial.println(Serial1.read(), BIN);
    Serial.println(Serial1.read(), BIN);
    Serial.println(Serial1.read(), BIN);
    Serial.println(" ");
    */

    Serial.println(" ");
    Serial.println("Contoller-----------------------------");

    while (Serials[ControllerSerial]->available() >= HowManyData )
    {
        while ( Serials[ControllerSerial]->available() >= HowManyData * 2  &&  Serials[ControllerSerial]->peek() != start )
        {
            Serials[ControllerSerial]->read();
        }
        
        dController.start = Serials[ControllerSerial]->read();
        if (uint8_t(dController.start) == start)
        {
            dController.one = Serials[ControllerSerial]->read();
            dController.two = Serials[ControllerSerial]->read();
            dController.three = Serials[ControllerSerial]->read();
            dController.four = Serials[ControllerSerial]->read();
            dController.five = Serials[ControllerSerial]->read();
            dController.six = Serials[ControllerSerial]->read();
            dController.seven = Serials[ControllerSerial]->read();
            dController.eight = Serials[ControllerSerial]->read();
            dController.fin = Serials[ControllerSerial]->read();

            if (uint8_t(dController.fin) == 0xAA)
            {
                dGood.one = dController.one;
                dGood.two = dController.two;
                dGood.three = dController.three;
                dGood.four = dController.four;
                dGood.five = dController.five;
                dGood.six = dController.six;
                dGood.seven = dController.seven;
                dGood.eight = dController.eight;
                dGood.fin = dController.fin;
            }
        }
    }

    if ( uint8_t(dGood.one) == 0xDD && uint8_t(dGood.two) == 0xDD && uint8_t(dGood.three) == 0xDD && u_int8_t(dGood.four) == 0xDD && uint8_t(dGood.five) == 0xDD && uint8_t(dGood.six) == 0xDD)
    {
        Serial.println("unpearing");
        ContollerConnected = 0;
    }
    else
    {
        ContollerConnected = 1;
        Serial.print(dGood.one);
        Serial.print(", ");
        Serial.print(dGood.two);
        Serial.print(", ");
        Serial.print(dGood.three);
        Serial.print(", ");
        Serial.print(dGood.four);
        Serial.print(", ");
        Serial.print(dGood.five, BIN);
        Serial.print(", "); 
        Serial.print(dGood.six, BIN); 
        Serial.print(", ");
        Serial.print(dGood.seven);
        Serial.print(", ");
        Serial.println(dGood.eight);
    }

    if (L.lastStickpower > L.Stickpower())
    {
        L.Stickpower2 = L.Stickpower();
    }
    if (R.lastStickpower > R.Stickpower())
    {
        R.Stickpower2 = R.Stickpower();
    }

    Serial.print(L.sinStick());
    Serial.print(", ");
    Serial.print(L.cosStick());
    Serial.println(", ");


    L.x = dGood.one;
    L.y = dGood.two;
    R.x = dGood.three;
    R.y = dGood.four;
    L.lastStickpower = L.Stickpower();
    R.lastStickpower = R.Stickpower();
    L.ana2 = dGood.seven;
    R.ana2 = dGood.eight;


    Serial.print("L.Stickdeg: ");
    Serial.print( L.Stickdeg() );
    Serial.print(", R.Stickdeg: ");
    Serial.print( R.Stickdeg() );
    Serial.print(",  L.Stickpowe: ");
    Serial.print( L.Stickpower() );
    Serial.print(", R.Stickpowe: ");
    Serial.print( R.Stickpower() );



    //クリックしているかの、配列を作成。
    for (int i = 0; i < 8; i++)
    {
        if ( (dGood.five >> Key1.Numbers[i] & 0b01) == 0b01 )
        {
            Key1.values[i] = true;
        }
        else
        {
            Key1.values[i] = false;
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if ( (dGood.six >> Key2.Numbers[i] & 0b01) == 0b01)
        {
            Key2.values[i] = true;
        }
        else
        {
            Key2.values[i] = false;
        }
    }

    //配列を確認して、どのキーが押されているかを表示。"Key?.values[Defineしたkeys] == true"でいけます。
    for (int i = 0; i < 8; i++)
    {
        if (Key1.values[Key1.Numbers[i]] == true)
        {
            Serial.print(Key1.Names[i]);
            Serial.print(", ");
        }
    }
    for (int i = 0; i < 8; i++)
    {
        if (Key2.values[Key2.Numbers[i]] == true)
        {
            Serial.print(Key2.Names[i]);
            Serial.print(", ");
        }
    }

    Serial.println(" ");

}

//00000000