#include "mbed.h"
#include "blinkThread.h"
#include "temperature.h"
#include "GUI.h"
#include "displayThread.h"
#include "capsenseThread.h"

Thread blinkThreadHandle;
Thread temperatureThreadHandle;
Thread displayThreadHandle;
Thread capsenseThreadHandle;

int main()
{

    blinkThreadHandle.start(blinkThread);
    displayThreadHandle.start(displayThread);
    temperatureThreadHandle.start(temperatureThread);
    capsenseThreadHandle.start(capsenseThread);

}

