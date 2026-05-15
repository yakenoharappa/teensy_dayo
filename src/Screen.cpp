#include <Wire.h>
#include <math.h>


#include "Screen.h"


//kicker.cppへ
bool KickerOnOff = 1;

//controller.cppへ
bool ContollerConnected = 1;


//Motor.cpp
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

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Status now = Status::Menu;

UltraSonic MyUSonic;


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
    if ( digitalRead(Senter) == HIGH && (millis() - LastTouched) > 300 )
    {
        LastTouched = millis();
        return true;
    }
    else{
        return false;
    }
    
}

bool UpKey(){
    if ( digitalRead(front) == HIGH && (millis() - LastTouched) > 300 )
    {
        LastTouched = millis();
        return true;
    }
    else{
        return false;
    }
    
}



bool DownKey(){
    if ( digitalRead(buttom) == HIGH && (millis() - LastTouched) > 300 )
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
    for (int i = 0; i < MyUSonic.amount; i++){
        MyUSonic.value[i] ++;
    }

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
        //BNOdeg.degf = yaw_BNO;
        //MIXdeg.degi = DAC_port;
        //LSMdeg.degf = theta;

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

        display.drawLine(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 , (SCREEN_WIDTH/2 + senga_X2 + 0), (SCREEN_HEIGHT/2 - senga_Y2), WHITE);
        display.drawLine(SCREEN_WIDTH/2 + 35, SCREEN_HEIGHT/2 , (SCREEN_WIDTH/2 + senga_X2 + 35), (SCREEN_HEIGHT/2 - senga_Y2), WHITE);
        display.drawLine(SCREEN_WIDTH/2 - 35, SCREEN_HEIGHT/2 , (SCREEN_WIDTH/2 + senga_X2 - 35), (SCREEN_HEIGHT/2 - senga_Y2), WHITE);
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
        display.println(Sita);

        if ( digitalRead(Senter) == HIGH && (millis() - LastTouched) > 300)
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

        if ( digitalRead(front) == HIGH && (millis() - LastTouched) > 300 )
        {
            LeftRight --;
            LastTouched = millis();
        }
        else if (digitalRead(buttom) == HIGH && (millis() - LastTouched) > 300 ){
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


        if ( digitalRead(Senter) == HIGH && (millis() - LastTouched) > 300)
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
        display.println("Please wait");
        for (int i = senter_square(SCREEN_WIDTH - 10); i < SCREEN_WIDTH - senter_square(SCREEN_WIDTH - 10) ; i++){
            display.drawLine(senter_square(SCREEN_WIDTH - 10), 50, i, 50, WHITE);
            display.display();
            delay(1);
        }
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
            writefillCircle(35, 15, 2);
            writefillCircle(-35, 15, 2);
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
        break;
    case Status::Speed:
        display.setTextSize(2);
        display.setCursor(0, 0);
        display.println("Speed");
        display.setTextSize(1);
        display.print("Speed: ");
        display.print(MotorSpeed);
        display.println("%");
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
        else if (digitalRead(front) == HIGH && (millis() - LastTouched) > 75 && MotorSpeed < 100){
            MotorSpeed++;
        }
        else if (digitalRead(buttom) == HIGH && (millis() - LastTouched) > 75 && MotorSpeed > 0){
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
        if (UpKey() == true ){
            Timer++;
        }
        else if (DownKey() == true )
        {
            Timer--;
        }
        else if (digitalRead(front) == HIGH && (millis() - LastTouched) > 80 ){
            Timer++;
        }
        else if (digitalRead(buttom) == HIGH && (millis() - LastTouched) > 80 ){
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