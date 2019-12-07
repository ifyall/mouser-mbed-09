#include "mbed.h"
#include "blinkThread.h"
#include "temperatureThread.h"
#include "displayThread.h"

DigitalOut led1(LED1);

void blinkThread()
{
    ThisThread::sleep_for(250);
 
    while (true) 
    {
        led1 = !led1;
        displaySendUpdateTime();
        ThisThread::sleep_for(500);
    }
}
