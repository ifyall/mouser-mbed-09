#include "mbed.h"
#include "blinkThread.h"
#include "temperatureThread.h"
#include "GUI.h"
#include "displayThread.h"
#include "capsenseThread.h"
#include "ntpThread.h"
#include "awsThread.h"

Thread blinkThreadHandle;
Thread temperatureThreadHandle;
Thread displayThreadHandle;
Thread capsenseThreadHandle;
Thread ntpThreadHandle;
Thread awsThreadHandle;
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
    Timer *timer = new Timer();

    timer->start();

    printf("\033[2J\033[H"); // Clear Screen and go Home    
    printf("Started System\n");

    int ret;
    wifi = WiFiInterface::get_default_instance();
    timer->stop();
    int getInstUs = timer->read_us();

    timer->reset();
    timer->start();
    wifi->attach(&wifiStatusCallback);
    timer->stop();
    int attachUs = timer->read_us();

    printf("Get instance time (us): '%d'\n", getInstUs);
    printf("Attach time       (us): '%d'\n", attachUs);

    while(1)
    {
        timer->reset();
        timer->start();
        do {
            ret = wifi->connect("TheInternetsG", "expee41c", NSAPI_SECURITY_WPA_WPA2);
            if (ret != 0) {
            ThisThread::sleep_for(2000); // If for some reason it doesnt work wait 2s and try again
            }
        } while(ret !=0);
        timer->stop();
        int connectUs = timer->read_us();
        printf("Connect time      (us): '%d'\n", attachUs);

        if(blinkThreadHandle.get_state() == Thread::Deleted)
        {
            awsThreadHandle.start(awsThread);
            ntpThreadHandle.start(ntpThread);
            blinkThreadHandle.start(blinkThread);
            displayThreadHandle.start(displayThread);
            temperatureThreadHandle.start(temperatureThread);
            capsenseThreadHandle.start(capsenseThread);
        }
        WiFiSemaphore.acquire();
    }
}
