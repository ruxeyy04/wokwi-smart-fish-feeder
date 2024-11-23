#include <WiFi.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>
#include "wifiSetup.h"
#include "welcome.h"
#include "temp.h"
#include "ph.h"
#include "tds.h"
#include "food_storage.h"
#include "water_level.h"
#include "analyzeWater.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TDSSensor tds;

void setup()
{
  Serial.begin(115200);
  welcome();
  while (!Serial)
    ;
  wifiSetup();
  initTemperatureSensor();
  initPHSensor();
  initRelay();
  tds.begin();
}

void loop()
{
  display.clearDisplay();
  readTemp();
  float tdsValue = tds.readTDS(celsius);
  readTDS(tdsValue);
  readPH();
  displayPH();
  storageLevel();
  waterLevel();
  analyzeWater();
  display.display();
  delay(1000);
}

