#ifndef TEMPERATURE_H
#define TEMPERATURE_H

void temperatureThread();

void tempSendUpdateCurrentSetPointF(float delta);
void tempSendUpdateSetpointF(float setPoint);


#endif
