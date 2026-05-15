#include "MotorDriver.h"
#include "Serial.h"

//停止関数
void stop(){
    Serials[MOTORSerial]->println("1R0002R0003R0004R000");
}

//Motor関数動きますよ
void move(int motor1, int motor2, int motor3, int motor4){
/*     //なんかif文が来る
    if (_toggle_pin != 0xFF)
    {
        // if (digitalRead(_toggle_pin) == LOW)
        // {
        //     stop();
        //     return;
        // }
        static uint32_t last_ok_time = 0;
        if (digitalRead(_toggle_pin) == LOW)
        {
            if (millis() - last_ok_time > 50) // 50ms続いたら止める
            {
                _is_toggle_on = false;
                stop();
                return;
            }
        }
        else
        {
            last_ok_time = millis();
        } // 追加
    }
    _is_toggle_on = true; */

    int motors[5] = {0, motor1, motor2, motor3, motor4};
    String string_abs_motors[5] = {0, 0, 0, 0, 0};
    String string_value_motors[5] = {0, 0, 0, 0, 0};
    //motorの値を変換したいよ
    for (int i = 1; i <= 4 ; i++)
    {
        motors[i] = constrain(motors[i], -100, 100);
        string_abs_motors[i] = String(abs(motors[i]));
        //3桁に変換する。（すべて絶対値）
        if (abs(motors[i]) < 10)
        {
            string_abs_motors[i] = "00" + string_abs_motors[i];
        }
        else if (abs(motors[i]) < 100)
        {
            string_abs_motors[i] = "0" + string_abs_motors[i];
        }
        if ( motors[i] >= 0)  //ASK!!!!! 0のときはFなのRなの？
        {
            string_value_motors[i] = String(i) + "F" + string_abs_motors[i];
        }
        else{
            string_value_motors[i] = String(i) + "R" + string_abs_motors[i];
        }
        
    }
    Serials[MOTORSerial]->println(string_value_motors[1] + string_value_motors[2] + string_value_motors[3] + string_value_motors[4]);
}