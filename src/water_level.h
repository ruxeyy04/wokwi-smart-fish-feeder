#include <NewPing.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

// Water Level
#define WATER_TRIG_PIN 4
#define WATER_ECHO_PIN 13

#define MAX_DISTANCE 400
#define EMPTY_LEVEL 200
#define FULL_LEVEL 24

NewPing sonar1(WATER_TRIG_PIN, WATER_ECHO_PIN, MAX_DISTANCE);

int distance1;
int waterLevelPercent;

void waterLevel()
{
  delay(50); // Delay between pings to avoid excessive polling
  distance1 = sonar1.ping_cm();

  waterLevelPercent = map(distance1, EMPTY_LEVEL, FULL_LEVEL, 0, 100);
  waterLevelPercent = constrain(waterLevelPercent, 0, 100);

  display.setCursor(0, 30);
  display.print("Water Level : ");
  display.print(waterLevelPercent);
  display.println(" %");
}
