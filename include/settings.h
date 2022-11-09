#ifndef SETTINGS_H
#define SETTINGS_H
extern int minTemp;       //Minimum aquired iron tip temp during testing (°C)
extern int maxTemp;      //Maximum aquired iron tip temp during testing (°C)
extern int minADC;      //Minimum aquired ADC value during minTemp testing
extern int maxADC;      //Maximum aquired ADC value during minTemp testing
extern int minSettableTemp;       //Minimum selectable tip temp (°C)
extern int maxSettableTemp;      //Maximum selectable tip temp (°C)

extern int maxPWM;   //Maximum PWM Power
extern int avgCounts;     //Number of avg samples
extern int lcdInterval;   //LCD refresh rate (miliseconds) ;
#endif