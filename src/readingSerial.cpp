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
    
}