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

    uint32_t _baudrate;
    uint8_t _toggle_pin = 0xFF;

    bool _is_toggle_on = false;


void stop();
void move();