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
float tempGrams;
bool feedNowStatus = false;
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
TDSSensor tds;

#include "sendData.h"
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

unsigned long lastSendTime = 0; // Store the last time data was sent

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

  // Check if 5 seconds have passed since the last data send
  if (millis() - lastSendTime >= 5000) {
    sendData(celsius, ph_act, tdsValue, storageLevelPercent, waterLevelPercent, feedNowStatus, tempGrams * 1000);
    lastSendTime = millis(); // Update the last send time
  }

  display.display();
  delay(100);
}
