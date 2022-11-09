#include "header.h"
#include "settings.h"

#define tempSensor A0
#define knob A7
#define iron 10

struct sensorValues
{
    int knobRAW;
    float setTemp;
    float tempRAW;
    float currentTemp;
    float currentTempAVG;
    float setTempAVG;
};

float
    currentTemp = 0.0, // System Variable
    store = 0.0,       // System Variable
    knobStore = 0.0,   // System Variable
    currentTempAVG = 0,
    setTempAVG = 0;

int counter = 0;


sensorValues getAvarageValues(sensorValues values)
{
    if (counter < avgCounts)
    { // Sum up temp and knob data samples
        store = store + values.currentTemp;
        knobStore = knobStore + values.setTemp;
        counter++;
    }
    else
    {
        currentTempAVG = (store / avgCounts) - 1;    // Get temp mean (average)
        setTempAVG = (knobStore / avgCounts);        // Get knob - set temp mean (average)
        knobStore = 0;                                      // Reset storage variable
        store = 0;                                          // Reset storage variable
        counter = 0;                                        // Reset storage variable
    }

    values.currentTempAVG = currentTempAVG;
    values.setTempAVG = setTempAVG;

    return values;
}

// Sensors
sensorValues getSensorValues()
{
    sensorValues values = sensorValues();

    values.knobRAW = analogRead(knob);                                                  // Get analog value of Potentiometer
    values.setTemp = map(values.knobRAW, 0, 1023, minSettableTemp, maxSettableTemp);    // Scale pot analog value into temp unit

    values.tempRAW = analogRead(tempSensor);                                            // Get analog value of temp sensor
    values.currentTemp = map(analogRead(tempSensor), minADC, maxADC, minTemp, maxTemp); // Sacle raw analog temp values as actual temp units

    values = getAvarageValues(values);

    return values;
}
