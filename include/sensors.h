#ifndef SENSORS_H
#define SENSORS_H

struct sensorValues
{
    int knobRAW;
    float setTemp;
    float tempRAW;
    float currentTemp;
    float currentTempAVG;
    float setTempAVG;
};

sensorValues getSensorValues();

#endif