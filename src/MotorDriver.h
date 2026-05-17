#include <Arduino.h>
#include "Serial.h"



/* <memo>  ->   を完璧理解☆
    上記のような*Serialsの場合は、Serial.print();する場合も、*Serialsとしないと、うまくいかないね。
    しかしながら、(*Serials).print();とすると、カッコとかがついてめんどくさい。
    なので↓を使おう
    Serials->print();
    これは、(*Serials).print();と全くおんなじ意味だ。
    つまりこれは、*ポイントしたものの本体そのものを.以下する
    ということになるんだ！！！！！
*/


class MotorDriver
{
private:
    /* data */
public:
    enum class DriverNumber { DSR1202, ORIGINAL };
    int UsedDriver;
    uint8_t Start_Header;
    uint8_t End_Footer;


    void stop();
    void move(int motor1, int motor2, int motor3, int motor4);
    void sendMotor(int16_t value1, int16_t value2, int16_t value3, int16_t value4);
};