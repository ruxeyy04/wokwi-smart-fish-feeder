#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

// Water Temperature
#define ONE_WIRE_BUS 17

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);
float celsius = 0;

void initTemperatureSensor() {
  tempSensor.begin();
}

float getTemperatureCelsius() {
  tempSensor.requestTemperatures();
  return tempSensor.getTempCByIndex(0);
}
void readTemp() {

  celsius = getTemperatureCelsius();

  // Display temperature
  Serial.print(celsius);
  Serial.println(" C");
  display.setCursor(0, 0);
  display.print("Temperature: ");
  display.print(celsius, 1);
  display.println(" C");
}
