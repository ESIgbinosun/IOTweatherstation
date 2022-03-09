
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <WiFiClient.h>

ESP8266WiFiMulti WiFiMulti;
LiquidCrystal_I2C lcd(0x27,16,2);

void setup() {
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);
  // Serial.setDebugOutput(true);

  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("iotroam", "JSmdVaqTqt");
  //WiFiMulti.addAP("Ziggo9552054", "jm3Njqvqhhjf");

}

void loop() {
    int outdoorTemp;
    WiFiClient client;//
    DynamicJsonDocument jsonBuffer(1024);//
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;

    HTTPClient http;
    http.begin(client, "http://api.iot.hva-robots.nl/weather/Amsterdam");//
    int httpCode = http.GET();//

    if (httpCode == HTTP_CODE_OK) { // HTTP_CODE_OK == 200
    String payload = http.getString();//
    ///Serial.println(payload);

    deserializeJson(jsonBuffer, payload);

    outdoorTemp = jsonBuffer["temp_C"];
    //Serial.print("Outdoor temp in Amsterdam: ");
   //Serial.println(outdoorTemp);
   
    } else {
    Serial.println("Unable to connect :(");
    }

    Serial.print("[HTTP] begin...\n");
    int sensorValue = analogRead(A0);
    lcd.setCursor(12,0);
    lcd.print(sensorValue);
    lcd.setCursor(0,0);
    lcd.print("IndoorTemp:");
    lcd.setCursor(12,1);
    lcd.print(outdoorTemp);
    lcd.setCursor(0,1);
    lcd.print("outdoor:");

    
    String url = String("http://0d4f-145-109-154-166.ngrok.io/site/insert_db.php/?temperature=")+sensorValue;
    Serial.println(url);
    if (http.begin(client,url)) {  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
