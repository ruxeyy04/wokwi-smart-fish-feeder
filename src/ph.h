#include <Wire.h>
#include <SimpleTimer.h>
#include <Adafruit_SSD1306.h>
extern Adafruit_SSD1306 display;

// PH Level using Potentiometer
#define PH 34
SimpleTimer timer;

float calibration_value = 22.40 - 0.7;
int buffer_arr[10], temp;
float ph_act = 0;

void readPH();

void initPHSensor() {
  Wire.begin();
  timer.setInterval(1000L, readPH);
}

void readPH() {
  timer.run();
  int avgval = 0;

  for (int i = 0; i < 10; i++) {
    buffer_arr[i] = analogRead(PH);
    delay(30);
  }

  for (int i = 0; i < 9; i++) {
    for (int j = i + 1; j < 10; j++) {
      if (buffer_arr[i] > buffer_arr[j]) {
        temp = buffer_arr[i];
        buffer_arr[i] = buffer_arr[j];
        buffer_arr[j] = temp;
      }
    }
  }

  for (int i = 2; i < 8; i++) {
    avgval += buffer_arr[i];
  }

  float volt = (float)avgval * 3.3 / 4096.0 / 6;
  ph_act = -5.70 * volt + calibration_value;
}

void displayPH() {
  // Display pH value
  display.setCursor(0, 10);
  display.print("pH: ");
  display.println(ph_act, 1);
}
