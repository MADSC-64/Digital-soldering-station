#include "header.h"
#include "settings.h"
#include "sensors.h"

#define iron 10
#define LED 3

int pwm = 0; // System Variable

int criticalEventCheck(sensorValues values)
{
    if (values.tempRAW > maxADC)
    {
        return 1;
    }
    if (values.currentTemp > maxSettableTemp + 5)
    {
        return 2;
    }
    return 0;
}

// Heating
int heatingControll(sensorValues values)
{

    int criticalCheckStatus = criticalEventCheck(values);

    if(criticalCheckStatus != 0)  return criticalCheckStatus;

    if (analogRead(values.knobRAW) == 0)
    { // Turn off iron when knob as at its lowest (iron shutdown)
        digitalWrite(LED, LOW);
        pwm = 0;
    }
    else if (values.currentTemp <= values.setTemp)
    { // Turn on iron when iron temp is lower than preset temp
        digitalWrite(LED, HIGH);
        pwm = maxPWM;
    }
    else
    { // Turn off iron when iron temp is higher than preset temp
        digitalWrite(LED, LOW);
        pwm = 0;
    }

    analogWrite(iron, pwm); // Apply the aquired PWM value from the three cases above
    return 0;
}
