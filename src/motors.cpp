#include <Arduino.h>
#include "motors.hpp"
#include "Jyunya.h"
#include "readController.h"


// PIDの計算機実体を1つ作成
PID headingPID(2.5f, 0.01f, 0.1f, 0.2f); 

void motors_Setup()
{
    // シリアル
    Serial.begin(9600L); // デバッグ用

    motorsInit(&Serial1, 115200);            // モーター初期化

    motorsSetMoveSign(1, 1, 1, 1);           // 移動のための符号をセット
    motorsSetPdSign(1, 1, 1, 1);             // PID制御のための符号をセット
    motorsSetDegPosition(315, 45, 225, 135); // モータの物理位置をセット
    motorsStop();                            // 停止させておく

    // 不感帯の設定（0.5度以内のズレなら微調整を無視する）
    headingPID.setDeadband(0.5f);

    for (int i = 0; i < 20; i++)
    {
        motorsStop();
        delay(100);
    }
}

void motors_Update()
{
    // ==========================================
    // 1. 各種データの準備（本来はセンサーやコントローラから取得）
    // ==========================================
    float current_degree = 0.0f;  // 現在のロボットの向き（ジャイロの値をここに割り当てる）
    float target_degree = 0.0f;   // 目標とする向き（正面 = 0.0度）
    
    float move_direction = 0.0f;  // 移動したい方向（0度=前, 90度=右...）
    float move_power = 50.0f;      // 移動パワー（0 〜 100）

    // ==========================================
    // 2. motors.cpp 側のPID計算を更新
    // ==========================================
    // この1行で、内部の現在の向きと目標値の計算がすべて更新されます
    motorsPidProcess(&headingPID, DAC_port, R.Stickdeg() );

    // ==========================================
    // 3. モーター駆動
    // ==========================================
    if (move_power > 0.0f) 
    {
        // 移動入力がある場合は、移動しながらPIDで姿勢を維持する
        motorsMove(move_direction, move_power);
    } 
    else 
    {
        // その場に停止している場合は、PIDの力だけで正面を向く（旋回のみ）
        motorsPdMove(); 
    }

    delay(1); // 制御周期安定化のためのウェイト
}