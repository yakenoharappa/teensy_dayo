#include <Wire.h>
#include <math.h>


#include "Screen.h"


//kicker.cppへ
bool KickerOnOff = 1;

//controller.cppへ
//float motor_bias[4] = {1.00 , 1.00 , 1.00 , 1.00};


int MotorSpeed = 20;

//Timer.h ?
float Timer = 999999;


long LastTouched = millis();
int LeftRight = 0;
int TrySetup = 0; // 型（int）を忘れずに

int Menu_y = 0;

int HowManyLine = 8;
int Line_en_offset = 20;

bool bectol = 1;
int Sita = 0;
float radian = Sita * PI / 180;

int senga_Y2 = sin(radian);
int senga_X2 = cos(radian);


int Line_r = 30;
int LineSize = 6;
bool Line[8] = {0, 0, 0, 0, 0, 0, 0, 0};

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire1, -1);
Status now = Status::Menu;



//GyroREAD
Screen_Gyro BNOdeg;
Screen_Gyro MIXdeg;
Screen_Gyro LSMdeg;


class triangle
{
public:
    double main;
    
    double cosm(){
        return cos(main);
    }
    double sinm(){
        return sin(main);
    }
};

bool Enter(){
    if ( (digitalRead(Senter) == HIGH || (Key2.values[SELECT] && ContollerConnected == true) ) && (millis() - LastTouched) > 300 )
    {
        LastTouched = millis();
        return true;
    }
    else{
        return false;
    }
    
}

bool UpKey(){
    if (  (digitalRead(front) == HIGH|| (Key1.values[Up] && ContollerConnected == true) ) && (millis() - LastTouched) > 300 )
    {
        LastTouched = millis();
        return true;
    }
    else{
        return false;
    }
    
}



bool DownKey(){
    if ( (digitalRead(buttom) == HIGH || (Key1.values[Down] && ContollerConnected == true) ) && (millis() - LastTouched) > 300 )
    {
        LastTouched = millis();
        return true;
    }
    else{
        return false;
    }
}




int senter_square(int wide){
    int indent = (SCREEN_WIDTH - wide)/2;
    return indent;
}

void writeCircle(int x, int y, int r){
    display.drawCircle(SCREEN_WIDTH/2 + x, SCREEN_HEIGHT/2 + y, r, WHITE);
}

void writefillCircle(int x, int y, int r){
    display.fillCircle(SCREEN_WIDTH/2 + x, SCREEN_HEIGHT/2 + y, r, WHITE);
}

int dosu(int value){
    while (value > 360)
    {
        value -= 360;
    }
    while (value < 0)
    {
        value += 360;
    }
    return value;
}

int yakusu(int value, int shuki){
    while (value < 0)
    {
        value += shuki;
    }
    while (value >= shuki)
    {
        value -= shuki;
    }
    
    return value;
}



void Screen_Setup(){
    pinMode(front, INPUT_PULLDOWN);
    pinMode(Senter, INPUT_PULLDOWN);
    pinMode(buttom, INPUT_PULLDOWN);
    
    TrySetup = 0;
    Wire.begin();
    while (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C) && TrySetup < 3) 
    {
        Serial.println("Connecting...");
        delay(500);
        TrySetup++;
    }

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Hello, world!");
    display.display();
}

void Screen_Update(){


/*
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C) && TrySetup == 3){ //TrySetup==3つまり、失敗し続けた場合のみ実行。
        display.println("Try retrying.");
    }
*/
    display.clearDisplay();
/*  if (sennga_X2 == 20 ){
        sennga_X2 --;
        bectol = 0;
    }
    else if ( sennga_X2 == -20){
        sennga_X2 ++;
        bectol = 1;
    }
    else if (bectol == 0)
    {
        sennga_X2--;
    }
    else{
        sennga_X2++;
    }
    */
    display.drawLine(10, 13, SCREEN_WIDTH/3, 13, WHITE);


    Serial.print("button:");
    Serial.print(digitalRead(buttom));   //下
    Serial.print(", ");
    Serial.print(digitalRead(Senter));   //真ん中
    Serial.print(", ");
    Serial.println(digitalRead(front)); //上
    

/*
    if ( digitalRead(front) == HIGH && (millis() - LastTouched) > 300 && LeftRight > 0 )
    {
        LeftRight --;
        LastTouched = millis();
    }
    else if (digitalRead(buttom) == HIGH && (millis() - LastTouched) > 300){
        LeftRight ++;
        LastTouched = millis();
    }
*/


    switch (now)
    {
    case Status::Menu:
        display.setCursor(0, 0);
        display.setTextSize(2);
        display.println("Menu");

        display.setCursor(0, Menu_y);
        display.setTextSize(2);
        display.println(" ");
        display.setTextSize(1);
        display.println(" ");
        display.println("   Gyro");
        display.println(" ");
        display.println("   Line");
        display.println(" ");
        display.println("   Kicker");
        display.println(" ");
        display.println("   Controller");
        display.println(" ");
        display.println("   Speed");
        display.println(" ");
        display.println("   UltraSonic");
        display.println(" ");
        display.println("   Timer");
        display.println(" ");
        display.println("        v");


        //追加
        /* 構想
            ・Lineが伸びて、画面外に達したら打てる
            ・打てない間は、ブラックアウト（四角形を）
            ・打てるときは、白く塗りつぶし
        
        //↓ブラックアウトバージョン
        display.drawRect(0, 52, 128, 12, 1);
        display.setTextColor(1, 0);
        display.setTextWrap(false);
        display.setCursor(47, 54);
        display.print("Kicker");
        display.drawLine(0, 62, (millis() - LastKickedTime) * 128 / CoolTime, 62, 1);
        */
        if ( (millis() - LastKickedTime) > CoolTime && KickerOnOff == true)
        {
            display.fillRect(0, 52, 128, 12, WHITE);
            display.setTextColor(0);
            display.setTextWrap(false);
            display.setCursor(47, 54);
            display.print("Kicker");
            display.drawLine(0, 62, (millis() - LastKickedTime) * 128 / CoolTime, 62, BLACK);
        }
        else
        {
            display.drawRect(0, 52, 128, 12, 1);
            display.setTextColor(1, 0);
            display.setTextWrap(false);
            display.setCursor(47, 54);
            display.print("Kicker");
            display.drawLine(0, 62, (millis() - LastKickedTime) * 128 / CoolTime, 62, 1);
        }
        
        display.setTextColor(1);

        //end



        if ( UpKey() == true )
        {
            LeftRight --;
            LastTouched = millis();
        }
        else if ( DownKey() == true ){
            LeftRight ++;
            LastTouched = millis();
        }

        LeftRight = yakusu(LeftRight, 7);
        if (LeftRight < 3){
            Menu_y = -(LeftRight - 1) * 15;
        }
        else{
            Menu_y = -(LeftRight - 0.9) * 15 - LeftRight + 1;
        }
        display.drawRect(senter_square(SCREEN_WIDTH - 10), 37 ,(SCREEN_WIDTH - 10), 13, WHITE);



        if (abs(LeftRight) % 7 == 0){
            //display.drawRect(senter_square(SCREEN_WIDTH - 10), 22 ,(SCREEN_WIDTH - 10), 13, WHITE);
            if ( Enter() == true )
            {
                LastTouched = millis();

                now = Status::Gyro;
                LeftRight = 0;
            }
        }
        else if (abs(LeftRight) % 7 == 1)
        {
            //display.drawRect(senter_square(SCREEN_WIDTH - 10), 37 ,(SCREEN_WIDTH - 10), 13, WHITE);
            if ( Enter() == true )
            {
                LastTouched = millis();

                now = Status::Line;
                LeftRight = 0;
            }
        }
        else if (abs(LeftRight) % 7 == 2){
            //display.drawRect(senter_square(SCREEN_WIDTH - 10), 52 ,(SCREEN_WIDTH - 10), 13, WHITE);
            if ( Enter() == true )
            {
                LastTouched = millis();

                now = Status::Kicker;
                LeftRight = 0;
            }
        }
        else if (abs(LeftRight) % 7 == 3){
            //display.drawRect(senter_square(SCREEN_WIDTH - 10), 52 ,(SCREEN_WIDTH - 10), 13, WHITE);
            if ( Enter() == true )
            {
                LastTouched = millis();

                now = Status::Controller;
                LeftRight = 0;
            }
        }
        else if (abs(LeftRight) % 7 == 4){
            //display.drawRect(senter_square(SCREEN_WIDTH - 10), 52 ,(SCREEN_WIDTH - 10), 13, WHITE);
            if ( Enter() == true )
            {
                LastTouched = millis();

                now = Status::Speed;
                LeftRight = 0;
            }
        }
        else if (abs(LeftRight) % 7 == 5){
            if ( Enter() == true )
            {
                LastTouched = millis();

                now = Status::UltraSonic;
                LeftRight = 0;
            }
        }
        else if (abs(LeftRight) % 7 == 6){
            if ( Enter() == true )
            {
                LastTouched = millis();

                now = Status::Timer;
                LeftRight = 0;
            }
        }

        display.fillRect(0, 0, SCREEN_WIDTH, 18 , BLACK);
        display.setCursor(0, 0);
        display.setTextSize(2);
        display.println("Menu");
        display.drawLine(10, 13, SCREEN_WIDTH/3, 13, WHITE);

        Serial.print("LeftRight");
        Serial.println(LeftRight);

        

        break;
    
    case Status::Gyro:
        Sita ++;
        Sita = DegRangeChange(Sita, 180);
        BNOdeg.degf = yaw_BNO;
        MIXdeg.degi = DAC_port;
        LSMdeg.degf = theta;

        radian = deg_radian(Sita);
        senga_Y2 = cos(radian) * 15;
        senga_X2 = sin(radian) * 15;

        Serial.print(senga_X2);
        Serial.print(", ");
        Serial.println(senga_Y2);
        
        //writeCircle(20, 0, 30);
        //display.drawLine(SCREEN_WIDTH/2 + 20, SCREEN_HEIGHT/2 , (SCREEN_WIDTH/2 + senga_X2 + 20), (SCREEN_HEIGHT/2 - senga_Y2), WHITE);

        //test
        writeCircle(0, 0, 15);
        writeCircle(35, 0, 15);
        writeCircle(-35, 0, 15);

        display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 , (SCREEN_WIDTH/2 + (MIXdeg.sinGi() * 15) + 0), (SCREEN_HEIGHT/2 - (MIXdeg.cosGi() * 15)), WHITE);
        display.drawLine(SCREEN_WIDTH/2 + 35, SCREEN_HEIGHT/2 , (SCREEN_WIDTH/2 + (LSMdeg.sinGf() * 15) + 35), (SCREEN_HEIGHT/2 - (LSMdeg.cosGf() * 15)), WHITE);
        display.drawLine(SCREEN_WIDTH/2 - 35, SCREEN_HEIGHT/2 , (SCREEN_WIDTH/2 + (BNOdeg.sinGf() * 15) - 35), (SCREEN_HEIGHT/2 - (BNOdeg.cosGf() * 15)), WHITE);
        display.setTextSize(1);
        display.setCursor(20, 35);
        display.println("BNO");
        display.setTextSize(1);
        display.setCursor(56, 35);
        display.println("MIX");

        display.setTextSize(1);
        display.setCursor(91, 35);
        display.println("LSM");



        //Menu名
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Gyro");

        display.setTextSize(1);
        display.setTextColor(SSD1306_WHITE);
        display.setCursor(0, SCREEN_HEIGHT - 10);
        display.print("deg=");
        display.println(MIXdeg.degi);

        if ( Enter() == true )
        {
            LastTouched = millis();
            now = Status::Menu;
        }

        break;

    case Status::Line:
        //Menu名
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Line");


        //円を描く
        writeCircle(Line_en_offset, 0, Line_r);
        writeCircle(Line_en_offset, 0, 10);

        //Line描画
        //display.drawRect(senter_square(10), SCREEN_HEIGHT/2 - 10/2 ,10, 10, WHITE);
        //display.drawRect(senter_square(10) + Line_r, SCREEN_HEIGHT/2 - 10/2 ,10, 10, WHITE);

        if ( UpKey() == true )
        {
            LeftRight --;
            LastTouched = millis();
        }
        else if ( DownKey() == true ){
            LeftRight ++;
            LastTouched = millis();
        }


        
        if (abs(LeftRight) % 4 == 0)
        {
            for (int i = 0; i < 3; i++)
            {
                Line[i] = 1;
            }
            
        }
        else if (abs(LeftRight) % 3 == 0){
            for (int i = 3; i < 6; i++)
            {
                Line[i] = 1;
            }
            
        }
        else if (abs(LeftRight) % 2 == 0){
            for (int i = 6; i < 8; i++)
            {
                Line[i] = 1;
            }
            
        }
        else{
            for (int i = 0; i < 8; i++)
            {
                Line[i] = 0;
            }
        }

        for (int i = 0; i < HowManyLine ; i++){
            double OneDeg = 360 / HowManyLine;
            OneDeg = OneDeg * PI / 180;
            triangle Linedeg;
            Linedeg.main = OneDeg * i; 
            
            if (Line[i] == LOW){
                //display.drawRect(int(senter_square(LineSize) + (Linedeg.cosm() * (Line_r * 0.8)) + Line_en_offset), int (SCREEN_HEIGHT/2 - LineSize/2 - Linedeg.sinm() * (Line_r * 0.8)) ,LineSize, LineSize, WHITE);
                writeCircle(Line_en_offset + (Linedeg.cosm() * (Line_r * 0.8)), Linedeg.sinm() * (Line_r * 0.8), 3);
            }
            else{
                //display.fillRect(int(senter_square(LineSize) + Linedeg.cosm() * (Line_r * 0.8) + Line_en_offset), int (SCREEN_HEIGHT/2 - LineSize/2 - Linedeg.sinm() * (Line_r * 0.8)) ,LineSize, LineSize, WHITE);
                writefillCircle(Line_en_offset+ (Linedeg.cosm() * (Line_r * 0.8)), Linedeg.sinm() * (Line_r * 0.8), 3);
            }
        }


        if ( Enter() == true )
        {
            LastTouched = millis();
            LeftRight = 1;
            now = Status::Menu;
        }

        break;

    case Status::Kicker:
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Kicher");
        if (Enter() == true)
        {
            LeftRight = 2;
            now = Status::Menu;
        }

        display.setTextSize(1);
        display.println(" ");
        display.println("   ON!!!!(push upkey)");
        display.println(" ");
        
        if (DownKey() == true)
        {
            if (KickerOnOff == true)
            {
                KickerOnOff = false;
                display.println("   Kicker <OFF>");
            }
            else{
                KickerOnOff = true;
                display.println("   Kicker <ON>");
            }
            
        }
        else{
            if (KickerOnOff == true)
            {
                display.println("   Kicker <ON>");
            }
            else{
                display.println("   Kicker <OFF>");
            }
            
        }

        if (UpKey() == true)
        {
            now = Status::ONKicker;
        }
        
        display.println("   (Change: Down Key)");

        break;
    
    case Status::ONKicker:
        display.clearDisplay();
        display.drawRect(senter_square(SCREEN_WIDTH - 10), (SCREEN_HEIGHT - 40)/2 ,(SCREEN_WIDTH - 10), 40, WHITE);
        display.setTextSize(1);

        display.setCursor(15, 15);
        display.println("ON!!!!");
        display.setCursor(15, 30);
        
        Kick();
        display.println("Please wait");
        for (int i = senter_square(SCREEN_WIDTH - 10); i < SCREEN_WIDTH - senter_square(SCREEN_WIDTH - 10) ; i++){
            display.drawLine(senter_square(SCREEN_WIDTH - 10), 50, i, 50, WHITE);
            display.display();
            delay(1);
        }
        Kicker_end();

        LeftRight = 2;
        now = Status::Menu;
        
        break;

    case Status::Controller:
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Controller");

        if (ContollerConnected == true)
        {
            writeCircle(35, 15, 10);     //WriteLeftCircle
            writeCircle(-35, 15, 10);    //WriteRightCircle
            //スティックの座標に合わせて、変化させる。-128~128を-15~15に変換する。0.1171875をかける。
            writefillCircle(35 + (R.x * 15 / 128), 15 + (R.y * 15 / 128), 2);
            writefillCircle(-35 + (L.x * 15 / 128), 15 + (L.y * 15 / 128), 2);
            //配列を確認して、どのキーが押されているかを表示。"Key?.values[Defineしたkeys] == true"でいけます。
            display.setTextSize(1);
            for (int i = 0; i < 8; i++)
            {
                if (Key1.values[Key1.Numbers[i]] == true)
                {
                    display.print(Key1.Names[i]);
                    display.print(", ");
                }
            }
            for (int i = 0; i < 8; i++)
            {
                if (Key2.values[Key2.Numbers[i]] == true)
                {
                    display.print(Key2.Names[i]);
                    display.print(", ");
                }
            }
            display.println();
        }
        else{
            display.setTextSize(1);
            display.println("unpairing");
        }
        
        if (Enter() == true)
        {
            LeftRight = 3;
            now = Status::Menu;
        }
        else if ( UpKey() == true )
        {
            now = Status::ControllerB;
        }
        break;

    case Status::ControllerB:
        display.setTextColor(1, 0);
        display.setTextWrap(false);
        display.setCursor(0, 0);
        display.print("Contoller");

        if ( Key1.values[Right] == true )
            display.fillRect(32, 34, 7, 7, 1);  //right
        else
            display.drawRect(32, 34, 7, 7, 1);  //right

        if ( Key1.values[Down] == true )
            display.fillRect(24, 42, 7, 7, 1);  //down
        else
            display.drawRect(24, 42, 7, 7, 1);  //down

        if ( Key1.values[Left] == true )
            display.fillRect(16, 34, 7, 7, 1);  //left
        else
            display.drawRect(16, 34, 7, 7, 1);  //left

        if ( Key1.values[Up] == true )
            display.fillRect(24, 26, 7, 7, 1);  //up
        else
            display.drawRect(24, 26, 7, 7, 1);  //up

        if ( Key1.values[Cross] == true )
            display.fillCircle(94, 45, 4, 1);   //Cross
        else
            display.drawCircle(94, 45, 4, 1);   //Cross

        if ( Key1.values[Circle] == true )
            display.fillCircle(103, 36, 4, 1);  //Circle
        else
            display.drawCircle(103, 36, 4, 1);  //Circle

        if ( Key1.values[Square] == true )
            display.fillCircle(85, 36, 4, 1);   //Square
        else
            display.drawCircle(85, 36, 4, 1);   //Square

        if ( Key1.values[Triangle] == true )
            display.fillCircle(94, 27, 4, 1);   //Triangle
        else
            display.drawCircle(94, 27, 4, 1);   //Triangle

        //Stickの基準円
            display.drawCircle(44, 51, 9, 1);   //Left_Stick
            display.drawCircle(75, 51, 9, 1);   //Right_Stick

        if ( Key2.values[L3] == true )
            writefillCircle(11 + (L.x * 9 / 128), 19 + (L.y * 9 / 128), 2);
        else
            writeCircle(11 + (L.x * 9 / 128), 19 + (L.y * 9 / 128), 2);

        if ( Key2.values[R3] == true )
            writefillCircle(-20 + (R.x * 9 / 128), 19 + (R.y * 9 / 128), 2);
        else
            writeCircle(11 + (R.x * 9 / 128), 19 + (R.y * 9 / 128), 2);

        if ( Key2.values[START] == true )
            display.fillTriangle(68, 32, 78, 36, 68, 39, 1);    //START
        else
            display.drawTriangle(68, 32, 78, 36, 68, 39, 1);    //START

        if ( Key2.values[SELECT] == true )
            display.fillRect(43, 33, 11, 7, 1); //SELECT
        else
            display.drawRect(43, 33, 11, 7, 1); //SELECT

        if ( Key2.values[R2] == true )
            display.fillRect(82, 10, 24, 6, 1); //R2
        else
            display.drawRect(82, 10, 24, 6, 1); //R2
        
        if ( Key2.values[L2] == true )
            display.fillRect(15, 10, 24, 6, 1); //L2
        else
            display.drawRect(15, 10, 24, 6, 1); //L2

        if ( Key2.values[R1] == true )
            display.fillRect(82, 17, 24, 4, 1); //R1
        else
            display.drawRect(82, 17, 24, 4, 1); //R1

        if ( Key2.values[L1] == true )
            display.fillRect(15, 17, 24, 4, 1); //L1
        else
            display.drawRect(15, 17, 24, 4, 1); //L1

        if (Enter() == true)
        {
            LeftRight = 3;
            now = Status::Menu;
        }
        else if ( UpKey() == true )
        {
            now = Status::Controller;
        }
        break;

    case Status::Speed:
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Speed");
        display.setTextSize(1);
        display.print("Speed: ");
        display.print(MotorSpeed);
        display.println("%");

        //追加
        display.setTextSize(1);
        display.println();
        display.print("Speed: ");
        display.print(MotorSpeed);
        display.println("%");
        //end
        display.drawLine(15, SCREEN_HEIGHT/2 , (SCREEN_WIDTH - 30) * MotorSpeed /100 + 15 , SCREEN_HEIGHT/2, WHITE);
        display.drawCircle(15, SCREEN_HEIGHT/2, 1, WHITE);
        display.drawCircle(SCREEN_WIDTH - 15, SCREEN_HEIGHT/2, 1, WHITE);
        display.drawRect(senter_square(SCREEN_WIDTH - 30), (SCREEN_HEIGHT-6)/2 ,(SCREEN_WIDTH - 30), 6, WHITE);
        display.fillRect(15, (SCREEN_HEIGHT-6)/2, (SCREEN_WIDTH - 30) * MotorSpeed /100 + 1, 6, WHITE);
        if (UpKey() == true && MotorSpeed < 100){
            MotorSpeed++;
        }
        else if (DownKey() == true && MotorSpeed > 0)
        {
            MotorSpeed--;
        }
        else if ( (digitalRead(front) == HIGH || (Key2.values[Up] && ContollerConnected == true) ) && (millis() - LastTouched) > 75 && MotorSpeed < 100){
            MotorSpeed++;
        }
        else if ( (digitalRead(buttom) == HIGH || (Key2.values[Down] && ContollerConnected == true) ) && (millis() - LastTouched) > 75 && MotorSpeed > 0){
            MotorSpeed--;
        }
        

        if (Enter() == true)
        {
            LeftRight = 4;
            now = Status::Menu;
        }
        break;

    case Status::Runnning:
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Running");
        break;

    case Status::UltraSonic:
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("UltraSonic");
        display.setTextSize(1);
        for (int i = 0; i < MyUSonic.amount; i++ ){
            display.print("UltraSonic");
            display.print(MyUSonic.pin[i]);
            display.print(": ");
            display.println(MyUSonic.value[i]);
        }

        if (Enter() == true){
            LeftRight = 5;
            now = Status::Menu;
        }

        break;
    case Status::Timer:
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Timer");
        display.setTextSize(1);


        if (DownKey() == true)
        {
            if (Timer == 999999)
            {
                Timer = 300;
                
            }
            else{
                Timer = 999999;
                
            }
        }

        if (Timer != 999999)
        {
            display.println("   Timer <ON>");
            display.print("TimeLeft: ");
            display.print(int(Timer/60));
            if ( (Timer - (int(Timer/60)) * 60) <10)
            {
                display.print(":0");
            }else{
                display.print(":");
            }
            display.println(Timer - (int(Timer/60)) * 60);
        }
        else{
            display.println("   Timer <OFF>");
            display.println(" ");
        }
        display.println("   (Change: Down Key)");
        display.println("   (Select: Up Key)");

        if (UpKey() == true && Timer != 999999){
            now = Status::TimeSelect;
        }

        if (Enter() == true){
            LeftRight = 6;
            now = Status::Menu;
        }
        break;
    
    case Status::TimeSelect:
        display.fillRect(senter_square(SCREEN_WIDTH - 10), (SCREEN_HEIGHT+10)/2 ,(SCREEN_WIDTH - 10), 24, BLACK);
        display.drawRect(senter_square(SCREEN_WIDTH - 10), (SCREEN_HEIGHT+10)/2 ,(SCREEN_WIDTH - 10), 24, WHITE);
        display.setCursor(15, (SCREEN_HEIGHT+10)/2 + 3);
        display.println("ON!!!!");
        display.setCursor(15, (SCREEN_HEIGHT+10)/2 +13);
        display.println("Please wait");

        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println(" ");
        display.setTextSize(1);
        if (Timer != 999999)
        {
            display.println("   Timer <ON>");
            display.print("TimeLeft: ");
            display.print(int(Timer/60));
            if ( (Timer - (int(Timer/60)) * 60) <10)
            {
                display.print(":0");
            }else{
                display.print(":");
            }
            display.println(Timer - (int(Timer/60)) * 60);
        }
        else{
            display.println("   Timer <OFF>");
        }


    if (Timer != 999999){
        if ( UpKey() == true ){
            Timer++;
        }
        else if ( DownKey() == true )
        {
            Timer--;
        }
        else if ( (digitalRead(front) == HIGH || (Key2.values[Up] && ContollerConnected == true) ) && (millis() - LastTouched) > 80 ){
            Timer++;
        }
        else if ( (digitalRead(buttom) == HIGH || (Key2.values[Down] && ContollerConnected == true) ) && (millis() - LastTouched) > 80 ){
            Timer--;
        }
    }

        if (Enter() == true){
            now = Status::Timer;
        }
        break;
    }

    display.display();

    //delay(20);
}