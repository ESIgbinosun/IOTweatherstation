#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <ESP8266HTTPClient.h>

#include <WiFiClientSecureBearSSL.h>
#include <WiFiClient.h>

#define ONE_WIRE_BUS D5
#define MOTOR 0

ESP8266WiFiMulti WiFiMulti;
LiquidCrystal_I2C lcd(0x27, 16, 2);
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
//const uint8_t fingerprint[20] = {0xb4, 0x22, 0x73, 0x81, 0xc1, 0x21, 0x6b, 0x72, 0x5c, 0xcc, 0xd9, 0xc1, 0x2d, 0xfd, 0x9b, 0x90, 0x0b, 0xf8, 0xc7, 0xf8};
signed int outdoorTemp;
signed int cloudCover;
signed int windSpeed;
const int buttonPin = D7; 
int buttonState = 0; 



void setup() {
  lcd.init();
  lcd.backlight();
  sensors.begin();
  pinMode(buttonPin, INPUT);
  pinMode(MOTOR, OUTPUT);
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


  DynamicJsonDocument jsonBuffer(1024);//
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    //std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    //client->setFingerprint(fingerprint);

    //HTTPClient https;

    WiFiClient client;
    HTTPClient http;
    http.begin(client, "http://api.iot.hva-robots.nl/weather/Amsterdam/compact");//
    Serial.println(http.getString());
    int httpCode = http.GET();//
    Serial.println(httpCode);
    if (httpCode == HTTP_CODE_OK) { // HTTP_CODE_OK == 200
      String payload = http.getString();//
      Serial.println(payload);

      deserializeJson(jsonBuffer, payload);
   

      outdoorTemp = jsonBuffer["data"]["temp_C"].as<signed int>();
      cloudCover = jsonBuffer["data"]["cloudcover"].as<signed int>();
      windSpeed = jsonBuffer["data"]["windspeedKmph"].as<signed int>();
      //Serial.print("Outdoor temp in Amsterdam: ");
      Serial.println(outdoorTemp);
      http.end();

    } else {
      Serial.println("Unable to connect :( to api mats");
    }


    Serial.print("[HTTP] begin...\n");
    sensors.requestTemperatures();
    double sensorValue = sensors.getTempCByIndex(0);
    buttonState = digitalRead(buttonPin);


    if (buttonState == HIGH) {
        lcd.clear();
        lcd.setCursor(12, 0);
        lcd.print(cloudCover);
        lcd.setCursor(0, 0);
        lcd.print("Cloudcover:");
        lcd.setCursor(14, 0);
        lcd.print("%");
        lcd.setCursor(11, 1);
        lcd.print(windSpeed);
        lcd.setCursor(0, 1);
        lcd.print("Windspeed:");
        lcd.setCursor(13, 1);
        lcd.print("km");

   
    
  } else {
        lcd.clear();
        lcd.setCursor(8, 0);
        lcd.print(sensorValue);
        lcd.setCursor(0, 0);
        lcd.print("Indoor:");
        lcd.setCursor(13, 0);
        lcd.print("'C");
        lcd.setCursor(9, 1);
        lcd.print(outdoorTemp);
        lcd.setCursor(0, 1);
        lcd.print("outdoor:");
        lcd.setCursor(11, 1);
        lcd.print("'C");
  }

  if(windSpeed>10){
    analogWrite(0, 125);
  }else{
    analogWrite(0, 0);
  }
      
 

    String url = String("http://a2d1-145-109-135-180.ngrok.io/site/insert_db.php/?temperature=") + sensorValue + "&outdoor=" + outdoorTemp;
    Serial.println(url);
    HTTPClient client2;
    if (client2.begin(client, url)) { // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = client2.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = client2.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", client2.errorToString(httpCode).c_str());
      }

      client2.end();
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
  }

  delay(10000);
}
