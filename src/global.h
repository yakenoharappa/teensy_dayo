#pragma once
//yaw_BNOを共有

#include <Arduino.h>

//Jyroプログラム
void Jyunya_Setup();
void Jyunya_Update();

//OLED
void Screen_Setup();
void Screen_Update();

//Controllerプログラム
void readController_Setup();
void readController_Update();

//Kicker
#define FET1 2  //貯める
#define FET2 3  //放つ

//PIN OUTS
#define PIN_LED1 4  //LED(White)
#define PIN_LED2 5  //(Yellow)Seeduinoで使ってたLEDたち
#define PIN_LED3 6  //(Red)Seeduinoで使ってたLEDたち


//OLED_Buttons
#define Button1 10
#define Button2 11
#define Button3 12


//extern int LastTouched;

//extern int LeftRight;
//extern int TrySetup;



