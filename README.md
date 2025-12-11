# Simple Smartwatch

[![Platform](https://img.shields.io/badge/platform-ESP32-blue)](https://www.espressif.com/en/products/socs/esp32)  

A **simple smartwatch** project based on **ESP32 + SSD1306 OLED display**. This project demonstrates a basic smartwatch interface including time, steps, and battery level.

---

## Project Structure

README.md : Project information

software/ : Arduino code
	smartwatch.ino
	config.h

hardware/ : Components and wiring
	components.md

docs/ : Roadmap and future ideas
	roadmap.md


---

## Hardware Used

- **ESP32 Dev Module**  
- **OLED SSD1306 Display** (128x64, I2C)  
- **Button** (GPIO 0)  
- **3.7V Li-Ion Battery** (simulated in code)  

---

## Software – Required Libraries

Install via **Arduino Library Manager**:

- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)  
- [Adafruit SSD1306](https://github.com/adafruit/Adafruit_SSD1306)  

---

## Configuration – `software/config.h`

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

#define BUTTON_PIN 0

#endif

```

## Smartwatch Code – software/smartwatch.ino

```cpp
Copia codice
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int currentScreen = 0;
unsigned long lastUpdate = 0;

void setup(){
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("Display not found");
    while (true);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    currentScreen = (currentScreen + 1) % 3;
    delay(300);
  }

  if (millis() - lastUpdate > 1000) {
    lastUpdate = millis();
    updateScreen();
  }
}

void updateScreen() {
  display.clearDisplay();
  display.setCursor(0, 0);

  switch (currentScreen) {
    case 0:
      display.println("TIME");
      display.println("12:45");
      display.println("10/12/2025");
      break;

    case 1:
      display.println("STEPS");
      display.println("1234");
      break;

    case 2:
      display.println("BATTERY");
      display.println("85%");
      break;
  }

  display.display();
}

```

## Hardware Components – hardware/components.md

```md
# Hardware Components

## Microcontroller
- ESP32 Dev Module

## Display
- OLED SSD1306 128x64 (I2C)

## Connections
| OLED -> ESP32 |
| VCC -> 3.3V |
| GND -> GND |
| SDA -> GPIO 21 |
| SCL -> GPIO 22 |

## Button
- One terminal to GPIO 0
- Other terminal to GND

```
![Connection](images/connections/connections.png)
```

## Roadmap – docs/roadmap.md

```md
# Roadmap

- [ ] DS3231 RTC
- [ ] Real step counter (MPU6050)
- [ ] Bluetooth BLE
- [ ] Companion Android app
- [ ] Sleep mode for power saving

```

## How to Use
Clone this repository

Open software/smartwatch.ino with Arduino IDE

Select ESP32 Dev Module

Connect the ESP32 via USB

Upload the code







