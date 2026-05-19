#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include "global.h"
#include "readController.h"
#include "Screen.h"
#include "Kicker.h"
//#include "MotorDriver.h"
#include "motor_convert.h"
#include "motors.hpp"
//Alt+Shift+A → コメントアウトショートカット

/* Teensy 新規プロジェクトの作り方
1. Teensy_4.0を選択してプロジェクトを作成。
2. VSのエクスプローラを右クリックして、「ワークスペースにフォルダーを追加」
3. 
*/

/*includeパッチが認識されないときの対処法
① VS Code の IntelliSense を再生成する（最重要）
  PlatformIO の左側メニュー →
  （必ず、includeが認識されないファイルがマイコンに転送される状態に設定する（一番下のメニューで、希望するファイルが選ばれている。））
  「PROJECT TASKS」 → 「General」 → 「Rebuild IntelliSense Index」または、「Build」
  これを押すと、赤線が消えることが多いよ。
*/


motor_convert controller;

//おれは藤城や

void setup() {
    
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

    Serials[MOTORSerial]->begin(115200);
    //motorsInit(&Serial2, 115200);
    Serials[ControllerSerial]->begin(115200);

    Jyunya_Setup();
    readController_Setup();
    Kicker_Setup();
    motors_Setup();
    Screen_Setup();

}



void loop() {
    //GyroDataを更新
    Jyunya_Update();
    //basic_running(30,30,0,0);

    readController_Update();
    

/*     controller.MotorDeg(135, 45, 225, 315);
    if (L.Stickpower() > 2 && ContollerConnected == true)
    {
        controller.MotorPersents(L.Stickdeg());
    }
    else
    {
        controller.stoping();
    }   */

    motors_Update();

    Screen_Update();
    
    
    if (Key1.values[Cross] == HIGH && ContollerConnected == true)
    {
        Kick();
    }
    else if ( (millis() - LastKickedTime) >= 300 )
    {
        Kicker_end();
    } 


    delay(10); 
}
