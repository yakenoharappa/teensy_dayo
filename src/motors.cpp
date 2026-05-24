#include <Wire.h>

//#include "global.h"
#include "readController.h"
#include "Screen.h"
#include "Kicker.h"
//#include "MotorDriver.h"
//#include "motor_convert.h"
//#include "motors.hpp"
#include "PID.hpp"
#include "motors.hpp"

//motor_convert controller;

//おれは藤城や

/* void setup() {
    
    int TrySetup = 0;
    while (!Serial && TrySetup < 4)
    {
        Serial.begin(115200);
        TrySetup ++;
        delay(100);
    }

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_LED1, OUTPUT);
    pinMode(PIN_LED2, OUTPUT);
    pinMode(PIN_LED3, OUTPUT);

    Serial1.begin(115200);
    //motorsInit(&Serial2, 115200);
    Serial2.begin(115200);


    Jyunya_Setup();
    readController_Setup();
    Kicker_Setup();
    //motors_Setup();
    Screen_Setup();


} */

// PIDの計算機実体を1つ作成
PID headingPID(0.6f, 0.6f, 0.6f, 0.6f); 

void motors_Setup()
{
    // シリアル
    Serial.begin(115200); // デバッグ用

    digitalWrite(PIN_LED1, HIGH);
    //motorsInit(&Serial1, 115200);          // モーター初期化

    motorsSetMoveSign(-1, -1,- 1,- 1);       // 移動のための符号をセット
    motorsSetPdSign(1, 1, 1, 1);             // PID制御のための符号をセット
    motorsSetDegPosition(135, 45, 225, 315); // モータの物理位置をセット
    motorsStop();                            // 停止させておく

    // 不感帯の設定（0.5度以内のズレなら微調整を無視する）
    headingPID.setDeadband(10.0f);

    for (int i = 0; i < 20; i++)
    {
        motorsStop();
        delay(100);
    }
}

void motors_Update()
{

    // この1行で、内部の現在の向きと目標値の計算がすべて更新されます
    motorsPidProcess(&headingPID, yaw_BNO, 0.0f );
    float MotorMoveSpeed = L.Stickpower() * MotorSpeed / 180.31 ;
        if (Key2.values[L2] == HIGH && ContollerConnected == true )
        {
            if (L.ana2 != 0 )
            {
                MotorMoveSpeed = MotorMoveSpeed *  (1 + (L.ana2 / 255 * 0.6));  //*0.6を追加！！
            }
            else
            {
                MotorMoveSpeed = MotorMoveSpeed *  1.3;
            }
        }
        if (Key2.values[R2] == HIGH && ContollerConnected == true )
        {
            if (R.ana2 != 0 )
            {
                MotorMoveSpeed = MotorMoveSpeed *  (1 - (R.ana2 / 255 / 2));
            }
            else
            {
                MotorMoveSpeed = MotorMoveSpeed *  0.7;
            }
        
        }



    // ==========================================
    // 3. モーター駆動
    // ==========================================
    if (L.Stickpower() > 2 && ContollerConnected == true)   //move_power > 0.0f
    {
        if(R.Stickpower() > 2 && ContollerConnected == true)
        {
        motorsPidProcess(&headingPID, yaw_BNO, -R.Stickdeg());
        
        
        }
        
        
    // 移動入力がある場合は、移動しながらPIDで姿勢を維持する
    motorsMove(L.Stickdeg(), MotorMoveSpeed);
    
    } 

    else 
    {

        if(R.Stickpower() > 2 && ContollerConnected == true)
        {
        motorsPidProcess(&headingPID, yaw_BNO, -R.Stickdeg());
        
        
        }
    motorsPdMove();
       // motorsStop();
    }



   // Screen_Update();
    
    
/*     if (Key1.values[Cross] == HIGH && ContollerConnected == true)
    {
        Kick();
    }
    else if ( (millis() - LastKickedTime) >= 300 )
    {
        Kicker_end();
    } 
    delay(10); // 制御周期安定化のためのウェイト */
}