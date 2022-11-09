#include "header.h"
#include "sensors.h"
#include "display.h"
#include "heating.h"

#define tempSensor A0
#define knob A7
#define iron 10
#define LED 3
#define PGR D7
#define SET D6
#define BUZZER D5

//Pin Init
void InitPins(){
  pinMode(tempSensor,INPUT); //Set Temp Sensor pin as INPUT
  pinMode(knob,INPUT);       //Set Potentiometer Knob as INPUT
  pinMode(iron,OUTPUT);      //Set MOSFET PWM pin as OUTPUT
  pinMode(LED,OUTPUT);       //Set LED Status pin as OUTPUT
  pinMode(A6,INPUT);       //Passthru Pin 
}

void setup(){
  InitPins();
  InitScreen();
}



//Main Loop
void loop(){
  //Gets and processes sensor values
  sensorValues sensors = getSensorValues();

  //Performs heating cycle
  int heatingStatus = heatingControll(sensors);

  if(heatingStatus == 1) connectionWarning();
  if(heatingStatus == 2) overheatWarning();

  //Displays Data
  DisplayData(sensors);
}