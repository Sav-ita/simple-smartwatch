#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


int currentScreen = 0;
unsigned long lastUpdate = 0;


void setup()
{
pinMode(BUTTON_PIN, INPUT_PULLUP);
Serial.begin(115200);


if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR))
{
Serial.println("Display non trovato");
while (true);
}


display.clearDisplay();
display.setTextSize(1);
display.setTextColor(SSD1306_WHITE);
}


void loop()
{
if (digitalRead(BUTTON_PIN) == LOW)
{
currentScreen = (currentScreen + 1) % 3;
delay(300);
}


if (millis() - lastUpdate > 1000)
{
lastUpdate = millis();
updateScreen();
}
}


void updateScreen()
{
display.clearDisplay();
display.setCursor(0, 0);


switch (currentScreen)
{
case 0:
display.println("ORA");
display.println("12:45");
display.println("10/12/2025");
break;


case 1:
display.println("PASSI");
display.println("1234");
break;


case 2:
display.println("BATTERIA");
display.println("85%");
break;
}


display.display();
}