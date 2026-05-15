#pragma once

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "global.h"
#include "UltraSonic.h"
#include "convert.h"
#include "Jyunya.h"


//ButtonのPINを設定する。
#define Senter 11    //Decide
#define buttom 12    //Down
#define front 10     //Up

//Screen.cppで使用する && 外部で使用する可能性のある変数たち
extern int LeftRight;
extern long LastTouched;


#define SCREEN_WIDTH 128    //画面ピクセル幅
#define SCREEN_HEIGHT 64    //画面ピクセル高さ
extern Adafruit_SSD1306 display;
enum class Status { Menu, Gyro, Line, Kicker, ONKicker, Runnning, Controller, Speed, UltraSonic, Timer, TimeSelect };


class Screen_Gyro
{

public:
    float degf;
    int degi;
    float cosGf(){
        return cosf(degf);
    }
    float sinGf(){
        return sinf(degf);
    }

    float cosGi(){
        return cosf(degi);
    }
    float sinGi(){
        return sinf(degi);
    }
};
