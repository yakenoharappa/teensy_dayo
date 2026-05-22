
#include "global.h"
#include "Jyunya.h"
//注意！：通信中にSeeeduinoXiaoやBNO055などの電子部品に触れると燃えるので、絶対に触れないこと！！

// --- 設定（LSM） ---
auto& mySerial = Serial;
auto& myWire = Wire;



//LED ON OFF
#define ON HIGH //LED_ON
#define OFF LOW //LED_OFF

//LSM用
double theta = 0;
const double dt = 0.0008; 

//Address
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29, &Wire); //I2Cのアドレス定義
uint8_t lsm6_addr = 0x6A; // 通常は0x6Aか0x6B。結線に合わせて固定。

// レジスタアドレス(LSM)
constexpr uint8_t REG_WHO_AM_I = 0x0F;
constexpr uint8_t REG_CTRL1 = 0x10;
constexpr uint8_t REG_CTRL2 = 0x11;
constexpr uint8_t REG_OUTZ_L_G = 0x26; // Z軸のみ読み取る場合はここから

//BNO用
const int DAC_PIN = 0; //output_pin
const int Reset_Button = 23; //Reset_pin
static float Reset = 0;
float new_yaw = 0; //BNOnew
float new_check = 0;
float yaw_BNO = 0; //BNO
int BNObegin = 0;
unsigned long last_OKtime = 0;
//unsigned long time = 0;
float degcheck = 0;
float detectdeg = 0;
long checkTime = millis();
bool Button = 0;
int DAC_port = 0;

void writeReg(uint8_t reg, uint8_t val) {
    myWire.beginTransmission(lsm6_addr);
    myWire.write(reg);
    myWire.write(val);
    myWire.endTransmission();
}

bool lsm6_init() {
    uint8_t who;
    myWire.beginTransmission(lsm6_addr);
    myWire.write(REG_WHO_AM_I);
    myWire.endTransmission(false);
    myWire.requestFrom(lsm6_addr, (uint8_t)1);
    who = myWire.read();

    if (who != 0x70)
    {
        return false;
    }

    //ジャイロの有効化 (例: 120Hz, 2000dps)
    writeReg(REG_CTRL2, 0x6C); 
    return true;
}

//-180~180°の間に変換する
static float angle(float Angle){
    while (Angle < -180) Angle += 360;
    while (Angle >  180) Angle -= 360;
    return Angle;
}

void Jyunya_Setup() {
    Serial.print("hello");
    myWire.begin();

    pinMode(Reset_Button,INPUT_PULLDOWN); //内部プルアップを有効に

    //下記のOPERATION_MODE_IMUPLUSを追加してみました。どっちのほうがいいか、比較検討してみてください。

    //LSM__Weather Begin
    if (!lsm6_init()) {
        Serial.println("LSM6DSV16X not found!");
        while (1);
    }
    Serial.println("LSM6DSV16X Ready.");

    while (!bno.begin(OPERATION_MODE_IMUPLUS) && BNObegin < 4) {
        Serial.println("BNO055 was not found!");
        BNObegin++;
        delay(500);
    }
    bno.setExtCrystalUse(true); //必要かどうかわからんけど、性能向上するだろうか、いや、しない。
    //float CalibTime = millis();
}




void Jyunya_Update() {
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER); //BNO055からオイラー角を入手

    // Z軸ジャイロデータのみ読み取り
    uint8_t buf[2];
    myWire.beginTransmission(lsm6_addr);
    myWire.write(REG_OUTZ_L_G);
    myWire.endTransmission(false);
    myWire.requestFrom(lsm6_addr, (uint8_t)2);
    buf[0] = myWire.read();
    buf[1] = myWire.read();
    int16_t gz_raw = (buf[1] << 8 | buf[0]);

    Button = digitalRead(Reset_Button);
//boolとは、０か１か（true or false）を表す変数。intより更に処理が簡潔なので、処理速度の向上が見込まれる。

    // 2000dps設定時の感度(約70mdps/LSB)を掛けて度数法に変換
    float gz = static_cast<float>(gz_raw) * -0.07;
    // 積分
    theta += gz * dt;

    //元の若松pでは、0~360度にしているが、ここでは、-180~180度に統一
    theta = angle(theta);

//再起動（リスタート）
    new_yaw = euler.x();

    /* 2026/04/07_18:00
    if ( fabs(new_check - new_yaw) <= 0.05 )
    {
        if ( millis() - last_OKtime > 1000 )
        {
            Serial.print("oh died!?");
            degcheck = yaw_BNO;
        }
    }
    else
    {
        if ( millis() - last_OKtime > 1000 )
        {
            degcheck = yaw_BNO;
        }
    }
    */

    //yaw_BNO has not Defined

    /* 
    if (Button = 0) new_yaw -= Reset;
    Serial.print("Reset途中:");
    Serial.println(new_yaw);
    */


//リセットボタン
    if (Button == 1 || Key2.values[R3] == true)
    {
        Reset = new_yaw;
        theta = 0; //LSM用
        Serial.print("Button");
        Serial.print(Reset);
        //digitalWrite(PIN_LED3, ON);
    }
    else
    {
        //digitalWrite(PIN_LED3, OFF);
    }
    new_yaw = new_yaw - Reset;
    new_yaw = angle(new_yaw);
    Serial.print("途中:");
    Serial.println(new_yaw);

    if ( isnan(new_yaw) || ( fabs(new_check - new_yaw) <= 0.03 && fabs(new_yaw - theta) > 20 ) ) //ぶっ壊れor変化無し
    {
        if ( fabs(millis() - last_OKtime) > 150 && fabs(new_yaw) >= 0.06 ) //時間がちょいたちand0.06°以上
        {
            DAC_port = theta;
        }
        else if ( fabs(millis() - last_OKtime) > 500 && fabs(new_yaw) >= 0.06 ) //時間がたちand0.06°以上
        {
            degcheck = yaw_BNO;
            Serial.print("error!!");
            //I2Cをやり直す（I2Cをリスタート）
            if ( BNObegin < 3 )
            {
                /*
                Wire.end();
                delay(10);
                Wire.begin();
                */
                if ( !bno.begin(OPERATION_MODE_IMUPLUS ) )
                {
                    Serial.print("BNO055 could't restart");
                }
                else
                {
                    Serial.print("BNO recovered!!");
                }
            }
            
            new_yaw = euler.x();
            detectdeg += degcheck - new_yaw; //新10_旧0
            //last_OKtime = millis(); //ここじゃないと、二個目のifの意味がなくなるよ
            new_check = new_yaw;
            DAC_port = theta;
        }
        else
        {
            DAC_port = yaw_BNO;
        }
    }
    else
    {
        Serial.print("LSM中");
        if ( fabs(millis() - last_OKtime) < 1000 )
        {
            degcheck = yaw_BNO;
            new_check = new_yaw;
            last_OKtime = millis();
            if (fabs(new_yaw - theta) < 20)
            {
                theta = yaw_BNO;
            }
        }
        /*
        else if (fabs(new_yaw - theta) < 20)
        {
            theta = yaw_BNO;
        }
        */
        
        DAC_port = yaw_BNO;

    }

    yaw_BNO = new_yaw + detectdeg;


    //float pitch = euler.y();
    //float roll = euler.z();

//旧reset_position


    if ( fabs(yaw_BNO - theta) < 20 && fabs(new_check - new_yaw) >= 0.07 )
    {
        
        //DAC_port = yaw_BNO;
        //theta = yaw_BNO;
        
    }
    else
    {
        if ( fabs(millis() - checkTime) >= 30 )
        {
            Serial.println("plusing");
            theta += 0.01;
            checkTime = millis();
        }
        //DAC_port = theta;
    }


//DAC変換
    yaw_BNO = angle(yaw_BNO);
    int dacvalue = (DAC_port + 180) * 1023 / 360;


//LED
    if ( fabs(DAC_port) < 10 )
    {
        digitalWrite(LED_BUILTIN, ON);
        //digitalWrite(PIN_LED2, OFF);
    }
    else if ( fabs(DAC_port) > 170 )
    {
        digitalWrite(LED_BUILTIN, OFF);
        //digitalWrite(PIN_LED2, ON);
    }
    else
    {
        digitalWrite(LED_BUILTIN, OFF);
        //digitalWrite(PIN_LED2, OFF);
    }


//DAC転送
    //float omega_out = (theta / 360.0) * 1023.0; //(LSM)
    //analogWrite(DAC_PIN, (int)omega_out);
    //analogWrite(DAC_PIN, dacvalue); //TJ3Bcoreに転送する（BNO）


    //Serial.print(Reset);
    Serial.print("角度:" );
    Serial.print(yaw_BNO);
    Serial.print(", Theta: ");
    Serial.println(theta);
    Serial.print(", DAC_port: ");
    Serial.println(DAC_port);

    /*
    Serial.print("value=");
    Serial.print(dacvalue);
    Serial.print(","); 
    Serial.print(pitch); 
    Serial.print(","); 
    Serial.print(roll);
    Serial.println(",");
    */
    
}