#include "mbed.h"
#include "ntp-client/NTPClient.h"

extern WiFiInterface *wifi;


void NTPThread()
{
    NTPClient ntpclient(wifi);
 
    while(1)
    {
        if(wifi->get_connection_status() == NSAPI_STATUS_GLOBAL_UP)
        {
            time_t timestamp = ntpclient.get_timestamp();
            if (timestamp < 0) {
                // probably need to do something different here
            } 
            else 
            {
                set_time(timestamp);
            }
        }
        ThisThread::sleep_for(1000*60*5); // Goto the NTP server every 5 minutes
    }
}