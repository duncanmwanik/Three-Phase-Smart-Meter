#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <def.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET -1    // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void testdrawline()
{
  int16_t i;

  display.clearDisplay(); // Clear display buffer

  for (i = 0; i < display.width(); i += 4)
  {
    display.drawLine(0, 0, i, display.height() - 1, WHITE);
    display.display(); // Update screen with each newly-drawn line
    delay(1);
  }
  for (i = 0; i < display.height(); i += 4)
  {
    display.drawLine(0, 0, display.width() - 1, i, WHITE);
    display.display();
    delay(1);
  }
  delay(250);
  delay(2000); // Pause for 2 seconds
}

void setupOLED()
{
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("SSD1306 init failed"));
  }
  display.display();
  delay(2000); // Pause for 2 seconds
  display.clearDisplay();
  display.drawPixel(10, 10, WHITE);
  display.display();
  delay(2000);

  testdrawline();
  Serial.println("OLED setup......");
}

void displayData()
{
  display.clearDisplay();

  display.setTextSize(1.2);    // Normal 1:1 pixel scale
  display.setTextColor(WHITE); // Draw white text
  display.setCursor(0, 0);     // Start at top-left corner

  String phase1info = "P1: V=" + String(V_P1) + " I=" + String(A_P1) + "       W=" + String(W_P1);
  String phase2info = "P2: V=" + String(V_P2) + " I=" + String(A_P2) + "       W=" + String(W_P2);
  String phase3info = "P3: V=" + String(V_P3) + " I=" + String(A_P3) + "       W=" + String(W_P3);

  display.println(phase1info);
  display.println("---------------------");
  display.println(phase2info);
  display.println("---------------------");
  display.println(phase3info);

  display.display();
}