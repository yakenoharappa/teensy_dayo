#include "readingSerial.h"

readingSerial::readingSerial(int number, uint8_t StartC, uint8_t endC, int amount)
{
    readingSerial::SerialNumber = number;
    readingSerial::Start = StartC;
    readingSerial::End = endC;
    readingSerial::amountData = amount;
    
}

void readingSerial::readData()
{
    while (Serials[SerialNumber]->available() >= amountData )
    {
        while ( Serials[SerialNumber]->available() >= readingSerial::amountData * 2  &&  Serials[SerialNumber]->peek() != readingSerial::amountData )
        {
            Serials[SerialNumber]->read();
        }
        
        readingSerial::checkV[0] = Serials[SerialNumber]->read();
        if (uint8_t(readingSerial::checkV[0]) == readingSerial::amountData)
        {
            for (int i = 0; i < readingSerial::amountData; i++){
                readingSerial::checkV[i] = Serials[SerialNumber]->read();
            }

/*             dController.two = Serials[SerialNumber]->read();
            dController.three = Serials[SerialNumber]->read();
            dController.four = Serials[SerialNumber]->read();
            dController.five = Serials[SerialNumber]->read();
            dController.six = Serials[SerialNumber]->read();
            dController.fin = Serials[SerialNumber]->read();
            */

            if (uint8_t(Serials[SerialNumber]->read()) == 0xAA)
            {
            for (int i = 0; i < readingSerial::amountData; i++){
                readingSerial::values[i] = readingSerial::checkV[i];
            }
/*                 dGood.one = dController.one;
                dGood.two = dController.two;
                dGood.three = dController.three;
                dGood.four = dController.four;
                dGood.five = dController.five;
                dGood.six = dController.six;
                dGood.fin = dController.fin; */
            }
        }
    }
}