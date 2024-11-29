#ifndef SEND_DATA_H
#define SEND_DATA_H

#include <HTTPClient.h>
#include <ArduinoJson.h>

const String POST_API_URL = "https://jasfrullah-fishfeed.bytevortexz.com/api/esp32/send_data";
const String POST_DEVICE_ID = "IFEED0001";
extern bool feedNowStatus;
bool sendData(float temperature, float pH, float turbidity, int foodStorage, int waterlevel, bool feedCondition, int feedGrams)
{
    // Prepare JSON payload
    DynamicJsonDocument doc(1024);
    doc["device_id"] = POST_DEVICE_ID;
    doc["temp"] = String(temperature, 1);
    doc["ph"] = String(pH, 1);
    doc["turbidity"] = String(turbidity, 1);
    doc["food_storage"] = String(foodStorage);
    doc["waterlevel"] = String(waterlevel);
    JsonObject feed = doc.createNestedObject("feed");
    feed["condition"] = feedCondition ? "true" : "false";
    feed["grams"] = String(feedGrams);

    String requestBody;
    serializeJson(doc, requestBody);

    // Setup HTTP client
    HTTPClient http;
    http.begin(POST_API_URL);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(requestBody);
    bool success = (httpResponseCode > 0);

    if (success)
    {
        Serial.printf("Data sent successfully, response code: %d\n", httpResponseCode);
    }
    else
    {
        Serial.printf("Error on HTTP request, code: %d\n", httpResponseCode);
    }
    if (feedNowStatus)
    {
        feedNowStatus = false;
    }

    http.end();

    return success;
}

#endif // SEND_DATA_H
