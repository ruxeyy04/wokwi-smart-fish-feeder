#include <NewPing.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

#define TRIG_PIN 12
#define ECHO_PIN 27

#define MAX_DISTANCE 400 
#define EMPTY_LEVEL 200   
#define FULL_LEVEL 24      

NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

unsigned int distance;
unsigned int storageLevelPercent;

void storageLevel() {
  delay(50);                   // Delay between pings to avoid excessive polling
  distance = sonar.ping_cm();  

  storageLevelPercent = map(distance, EMPTY_LEVEL, FULL_LEVEL, 0, 100);
  storageLevelPercent = constrain(storageLevelPercent, 0, 100);

  display.setCursor(0, 20);
  display.print("Storage : ");
  display.print(storageLevelPercent);
  display.println(" %");
}
