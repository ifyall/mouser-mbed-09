#include "mbed.h"
#include "blinkThread.h"
#include "temperature.h"
#include "GUI.h"
#include "displayThread.h"
#include "capsenseThread.h"
#include "ntpThread.h"

Thread blinkThreadHandle;
Thread temperatureThreadHandle;
Thread displayThreadHandle;
Thread capsenseThreadHandle;
Thread ntpThreadHandle;
Semaphore WiFiSemaphore;
WiFiInterface *wifi;

// wifiStatusCallback
// Changes the display when the wifi status is changed
void wifiStatusCallback(nsapi_event_t status, intptr_t param)
{
    switch(param) {
        case NSAPI_STATUS_LOCAL_UP:
        break;
        case NSAPI_STATUS_GLOBAL_UP:
        break;
        case NSAPI_STATUS_DISCONNECTED:
        WiFiSemaphore.release();
        break;
        case NSAPI_STATUS_CONNECTING:
        break;
        default:
        break;
    }
}

int main()
{

    printf("Started System\n");
#if 0
    ThisThread::sleep_for(2000); // If for some reason it doesnt work wait 2s and try again
    printf("Sleep done\n");
    ThisThread::sleep_for(2000); // If for some reason it doesnt work wait 2s and try again
#endif

    int ret;
    wifi = WiFiInterface::get_default_instance();
    wifi->attach(&wifiStatusCallback);
    while(1)
    {
        do {
            printf("Attempting connect\n");
            ret = wifi->connect("CYFI_IOT_EXT", "cypresswicedwifi101", NSAPI_SECURITY_WPA_WPA2);
            if (ret != 0) {
            ThisThread::sleep_for(2000); // If for some reason it doesnt work wait 2s and try again
            }
        } while(ret !=0);
        printf("Started WiFI\n");

        if(blinkThreadHandle.get_state() == Thread::Deleted)
        {
            ntpThreadHandle.start(NTPThread);
            blinkThreadHandle.start(blinkThread);
            displayThreadHandle.start(displayThread);
            temperatureThreadHandle.start(temperatureThread);
            capsenseThreadHandle.start(capsenseThread);
        }
        WiFiSemaphore.acquire();
    }
}


