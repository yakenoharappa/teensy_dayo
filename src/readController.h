#pragma once

#include <Arduino.h>
#include "convert.h"
#include "Serial.h"


const uint8_t start = 0x80 ;
const int HowManyData = 8;

class data
{

public:
    uint8_t start;
    int8_t one;
    int8_t two;
    int8_t  three;
    int8_t four;
    uint8_t five;
    uint8_t six;
    uint8_t fin;
};


//define KeyNumbers
#define Up 0
#define Left 1
#define Down 2
#define Right 3
#define Triangle 4
#define Circle 5
#define Cross 6
#define Square 7

#define SELECT 0
#define START 1
#define L1 2
#define L2 3
#define R1 4
#define R2 5
#define L3 6
#define R3 7



//M5側のinclude
class Stick
{
    public:
        int8_t x;
        int8_t y;
        float cosStick(){
            return x/128;
        }
        float sinStick(){
            return y/128;
        }
        float Stickdeg(){
            return atan2(-y, x);   //普通にatan2(y,x)で良い気がする。
        }
};

const String Keys1Name[8] = {"Up", "Left", "Down", "Right", "Triangle", "Circle", "Cross", "Square"};
const int Keys1[8] = {Up, Left, Down, Right, Triangle, Circle, Cross, Square};
const int Keys2[8] = {SELECT, START, L1, L2, R1, R2, L3, R3};
const String Keys2Name[8] = {"SELECT", "START", "L1", "L2", "R1", "R2", "L3", "R3"};


class Button
{
    public:
        uint8_t value;
        bool values[8];
        int Numbers[8];
        String Names[8];
};



/* 
class ReadKey
{
public:

};

 */



//const uint8_t start = 0x80 ;
//前は(0b10100000)

/*00000000
1. 上
2. 左
3. 下
4. 右
5. 三角
6. 丸
7. バツ
8. 四角
*/


extern Stick L;
extern Stick R;
extern Button Key1;
extern Button Key2;