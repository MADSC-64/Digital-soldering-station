#ifndef DISPLAY_H
#define DISPLAY_H
#pragma once

void LoadCustomChars();
void InitScreen();

void DisplayData(sensorValues values);

void overheatWarning();

void connectionWarning();

#endif