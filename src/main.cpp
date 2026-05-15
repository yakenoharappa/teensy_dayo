#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//#include "global.h"
#include "readController.h"
#include "Screen.h"
#include "Kicker.h"
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


//おれは藤城や

void setup() {
    int TrySetup = 0;
    while (!Serial && TrySetup < 4)
    {
        Serial.begin(115200);
        TrySetup ++;
        delay(100);
    }




    //Jyunya_Setup();
    //readController_Setup();
    //Kicker_Setup();
    Screen_Setup();
    //Screen_Setup();

}



void loop() {
    //GyroDataを更新
    //Jyunya_Update();
    //basic_running(30,30,0,0);

    //readController_Update();
    Screen_Update();
    
    /* 
    if (Key1.values[Cross] == HIGH)
    {
        Kick();
    }
    */
    //Screen_Update();

    delay(10); 
}
