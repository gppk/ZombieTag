#pragma once
// Libraries for OLED Display
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED pins
#define OLED_INIT_DELAY (20)
#define OLED_SDA        (4)
#define OLED_SCL        (15)
#define OLED_RST        (16)
#define SCREEN_WIDTH    (128)   // OLED display width, in pixels
#define SCREEN_HEIGHT   (64)    // OLED display height, in pixels
#define START_OF_LINE   (0)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void clear_oled_line(uint lineNumberInPixels);

void init_oled() {
    // reset OLED display via software
    pinMode(OLED_RST, OUTPUT);
    digitalWrite(OLED_RST, LOW);
    delay(OLED_INIT_DELAY);
    digitalWrite(OLED_RST, HIGH);

    // initialize OLED
    Wire.begin(OLED_SDA, OLED_SCL);
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false,
                       false)) {   // Address 0x3C for 128x32
        Serial.println(F("SSD1306 allocation failed"));
        // TODO: This is probably bad inside a function like this. Rework to
        // make return a bool
        for (;;) {
        }   // Don't proceed, loop forever,
    }

    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1);
}

void write_oled_line(uint lineNumber, const char *data) {

    // Some really dumb and basic error handling because my screen
    // only has 5 lines to write to..
    if (lineNumber > 5 || lineNumber == 0)
        return;

    // line 1 = 10, 2 = 20, 3 = 30, 4 = 40, 5 = 50
    lineNumber = lineNumber * 10;
    clear_oled_line(lineNumber);
    display.setTextColor(WHITE, BLACK);
    // TODO: Need to clear the line first.
    display.setCursor(START_OF_LINE, lineNumber);
    display.print(data);
    display.display();
}

void write_oled_and_serial_line(uint lineNumber, const char *data) {
    write_oled_line(lineNumber, data);
    Serial.println(data);
}

// Internal function, only call after turning the devs lineNumber into pixels
// (i,e. * 10)
void clear_oled_line(uint lineNumberInPixels) {

    display.setTextColor(WHITE, BLACK);
    display.setTextSize(1);
    display.setCursor(START_OF_LINE, lineNumberInPixels);
    display.print("                        ");
    display.display();
}
