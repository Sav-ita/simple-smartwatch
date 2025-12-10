# Smartwatch Semplice

Progetto completo di **smartwatch semplice**, basato su **ESP32 + display OLED SSD1306**.

---

## Struttura

```
README.md : Informazioni sul progetto
software/ : Codice Arduino
  smartwatch.ino
  config.h
hardware/ : Componenti e collegamenti
  components.md
docs/ : Roadmap e idee future
  roadmap.md
```

---

## Hardware utilizzato

* ESP32 Dev Module
* Display OLED SSD1306 (128x64, I2C)
* Pulsante (GPIO 0)
* Batteria Li-Ion 3.7V (simulata nel codice)

---

## Software – Librerie richieste

Installa da **Arduino Library Manager**:

* Adafruit GFX Library
* Adafruit SSD1306

---

## File: `software/config.h`

```cpp
#ifndef CONFIG_H
#define CONFIG_H

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C

#define BUTTON_PIN 0

#endif
```

---

## File: `software/smartwatch.ino`

```cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int currentScreen = 0;
unsigned long lastUpdate = 0;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  Serial.begin(115200);

  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println("Display non trovato");
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
```

---

## File: `hardware/components.md`

```md
# Componenti hardware

## Microcontrollore
- ESP32 Dev Module

## Display
- OLED SSD1306 128x64 (I2C)

## Collegamenti
| OLED | ESP32 |
|-----|-------|
| VCC | 3.3V |
| GND | GND |
| SDA | GPIO 21 |
| SCL | GPIO 22 |

## Pulsante
- Un terminale a GPIO 0
- Altro a GND
```

---

## File: `docs/roadmap.md`

```md
# Roadmap

- [ ] RTC DS3231
- [ ] Contapassi reale (MPU6050)
- [ ] Bluetooth BLE
- [ ] App Android companion
- [ ] Modalità sleep per risparmio energetico
```

---

## Come usare il progetto

1. Clona la repo
2. Apri `software/smartwatch.ino` con Arduino IDE
3. Seleziona **ESP32 Dev Module**
4. Collega l'ESP32 via USB
5. Carica il codice

---


