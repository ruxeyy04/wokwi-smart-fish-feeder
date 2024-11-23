#ifndef ANALYZE_WATER_H
#define ANALYZE_WATER_H

#include "tds.h"
#include <Adafruit_SSD1306.h>

// OLED Display
extern Adafruit_SSD1306 display;

// Sensor Readings
extern float celsius;   // Temperature in Celsius
extern float ph_act;    // pH value
extern TDSSensor tds;   // TDS Sensor object
extern int waterLevelPercent; // Water level in percentage (0-100)

// Relays
#define RelayPump 16          // Relay for Water Replacement (Pump)
#define RelayDispenser 0      // Relay for Feeding (Feed Dispenser)
#define WaterCirculation 2    // Relay for Water Circulation

// TDS and pH thresholds
#define TDS_THRESHOLD 400.0
#define PH_MIN 6.0
#define PH_MAX 8.0
#define TEMP_HIGH 30.0
#define TEMP_LOW 27.0

// Water level thresholds
#define WATER_LEVEL_LOW 80
#define WATER_LEVEL_FULL 100

// Initialize relays
void initRelay() {
    pinMode(RelayPump, OUTPUT);
    pinMode(RelayDispenser, OUTPUT);
    pinMode(WaterCirculation, OUTPUT);
    digitalWrite(RelayPump, LOW);         // Default to OFF
    digitalWrite(RelayDispenser, LOW);   // Default to OFF
    digitalWrite(WaterCirculation, LOW); // Default to OFF
}

// Analyze water conditions and control relays
void analyzeWater() {
    // Read TDS value based on current water temperature
    float tdsVal = tds.readTDS(celsius);
    display.setCursor(0, 40);


    // Water circulation logic
    if (celsius > TEMP_HIGH) {
        digitalWrite(WaterCirculation, HIGH); // Turn ON circulation
        display.println("Circulating water...");
    } else if (celsius < TEMP_LOW) {
        digitalWrite(WaterCirculation, LOW); // Turn OFF circulation
        display.println("Circulation OFF");
    }

    // Water replacement logic
    if ((ph_act < PH_MIN || ph_act > PH_MAX) && tdsVal > TDS_THRESHOLD) {
        digitalWrite(RelayPump, HIGH); // Turn ON pump to replace water
        display.println("Replacing water...");
    } else if (waterLevelPercent < WATER_LEVEL_LOW) {
        // Refill water if the level is below 80%
        digitalWrite(RelayPump, HIGH);
        display.println("Refilling water...");
    } else {
        // Turn OFF pump if conditions are normal
        digitalWrite(RelayPump, LOW);
        display.println("Water OK!");
    }

    delay(1000); // Short delay for display refresh
}

#endif // ANALYZE_WATER_H
