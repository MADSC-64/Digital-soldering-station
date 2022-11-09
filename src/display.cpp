#include "header.h"
#include "symbols.h"
#include "settings.h"
#include "sensors.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 20, 4);

// System Variable
int previousMillis = 0;

// Warning Msg
char *overheatWarningMsg = "TOOL TOO HOT!!!       TURN OFF DEVICE!!!       TOOL TOO HOT!!!    ";
char *connectionWarningMsg = "NO TOOL DETECTED!!!       CHECK TOOL CONNECTION AND RESTART!!!       NO TOOL DETECTED!!!    ";
char *thermalRunawayWarningMsg = "THERMAL RUNAWAY!!!       INSPECT TOOL AND RESTART!!!       THERMAL RUNAWAY!!!    ";

void LoadCustomChars()
{
    lcd.createChar(0, arrowUpChar);
    lcd.createChar(1, arrowDownChar);
    lcd.createChar(2, thermometer);
    lcd.createChar(3, plugChar);
    lcd.createChar(4, socketChar);
}

// Screen Init
void InitScreen()
{
    lcd.backlight();
    lcd.init();
    LoadCustomChars();
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("TARGET:");
    lcd.setCursor(0, 0);
    lcd.print("CURENT:");
}

// Display
void DisplayData(sensorValues values)
{
    unsigned long currentMillis = millis(); // Use and aquire millis function instead of using delay
    if (currentMillis - previousMillis >= lcdInterval)
    { // LCD will only display new data ever n milisec intervals
        previousMillis = currentMillis;

        if (analogRead(values.knobRAW) == 0)
        {
            lcd.setCursor(8, 1);
            lcd.print("OFF  ");
        }
        else
        {
            lcd.setCursor(8, 1);
            lcd.print(values.setTempAVG, 1);
            lcd.print((char)223);
            lcd.print("C ");
        }

        lcd.setCursor(8, 0);
        lcd.print(values.currentTempAVG, 1);
        lcd.print((char)223);
        lcd.print("C ");
    }
}

// Scrolling Text
void showScrollingText(int printStart, int startLetter, char *msg, int speed = 250)
{
    lcd.setCursor(printStart, 1);
    for (int letter = startLetter; letter <= startLetter + 15; letter++) // Print only 16 chars in Line #2 starting 'startLetter'
    {
        lcd.print(msg[letter]);
    }
    delay(speed);
    lcd.print(" ");
}

// Warning Msgs
void overheatWarning()
{
    lcd.clear();

    // Draws Heat Symbol
    lcd.setCursor(0, 0);
    lcd.write(2);
    lcd.write(0);

    // Draws Warning Message
    lcd.setCursor(5, 0);
    lcd.print("!WARNING!");
    lcd.setCursor(5, 1);

    // Draws Scrolling Text
    for (int letter = 0; letter <= strlen(overheatWarningMsg) - 16; letter++) // From 0 to upto n-16 characters supply to below function
    {
        showScrollingText(0, letter, overheatWarningMsg);
    }

    // Delays Execution To Prevent Frequant Triggering
    delay(250);
}

void connectionWarning()
{
    lcd.clear();

    // Draws Heat Symbol
    lcd.setCursor(0, 0);
    lcd.write(1);
    lcd.write(3);
    lcd.setCursor(0, 1);
    lcd.write(0);
    lcd.write(4);

    // Draws Warning Message
    lcd.setCursor(5, 0);
    lcd.print("!WARNING!");
    lcd.setCursor(5, 1);

    // Draws Scrolling Text
    for (int letter = 0; letter <= strlen(connectionWarningMsg) - 16; letter++) // From 0 to upto n-16 characters supply to below function
    {
        showScrollingText(2, letter, connectionWarningMsg);
    }

    // Delays Execution To Prevent Frequant Triggering
    delay(250);
}