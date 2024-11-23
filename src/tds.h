#ifndef TDS_H
#define TDS_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

#define TDS_SENSOR_PIN 33

// Constants for TDS calculation
#define ADC_RESOLUTION 4096        
#define VREF 3.3                
#define TDS_FACTOR 0.5           

class TDSSensor {
public:
    TDSSensor(int pin = TDS_SENSOR_PIN) : sensorPin(pin) {}

    void begin() {
        pinMode(sensorPin, INPUT);
    }

    int readRaw() {
        return analogRead(sensorPin);
    }

    float readTDS(float temperature = 25.0) {
        int rawValue = readRaw();
        float voltage = (rawValue / float(ADC_RESOLUTION)) * VREF;
        float compensationCoefficient = 1.0 + 0.02 * (temperature - 25.0);
        float compensatedVoltage = voltage / compensationCoefficient;
        return compensatedVoltage * 1000 / TDS_FACTOR; 
    }

private:
    int sensorPin;
};

void readTDS(float val) {
  display.setCursor(60, 10);
  display.print("TDS: ");
  display.println(val, 1);
}
#endif // TDS_H
