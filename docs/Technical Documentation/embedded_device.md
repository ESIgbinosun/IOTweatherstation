# Embedded device Technical Documentation

## Device description

The weather mill stations a device that will show you the outdoor temperature and the indoor temperature. 
The station can indicate wind power by spinning the mill depending on the wind speed outside. The station LCD can display more data of the weather with a push of a button. 
The weather mill station is meant to reduce the use of a smartphone. If the user wants to track the weather data. 
The web application of the weather mill station will show a graphic of the indoor/outdoor temperature history. 

![design](IMGIOT/IOT windmill.jpg)

## Code description

Here in this code client session will be started to get data from the API:

```c++
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


```

## Wiring diagram

![Wiring diagram](IMGIOT/wiring diagram.png)


## Bill of Materials

|#| Part number  | Manufacturer  | Name    | Description                       | Quantity  | Cost   | url                                                                                                                                                                                                    |
|-|:------------:|:-------------:|:-------:|:---------------------------------:|:---------:|:------:| ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------:|
|1|KY-001        | Keyes         | DS18B20 | Temperatuur Sensor Module DS18B20 |  1X       | € 2,99 |  ![LINK](https://www.otronic.nl/a-63016282/sensors/temperatuur-sensor-module-ds18b20-dallas-clone/?gclid=Cj0KCQjwz7uRBhDRARIsAFqjuln9ZQj2s46OsvXAT7ZA9GZl4vI5bgohDp9vesoGXoXQkQr0cAALCawaAsyKEALw_wcB) |
|2|162LCD        |               | LCD     | LCD Display 16*2 characters       |  1x	 | € 4,00 |  ![LINK](https://www.tinytronics.nl/shop/en/displays/lcd/lcd-display-16*2-characters-with-white-text-and-blue-backlight)                                                                               |
|3|              |               | Wemos   | ESP8266 D1 Mini Pro		       |  1x       | € 9,99 |  ![LINK](https://www.otronic.nl/a-62361236/esp8266/esp8266-d1-mini-pro-development-board-wemos/?gclid=Cj0KCQjwz7uRBhDRARIsAFqjulmBhLtjCYMU66G0RRoBpKQh2jNPKogIFRLE5b-eb9luPoIChLH3fdgaAkBTEALw_wcB)    |
|4|              |               | DC      | DC motor                          |  1x       | € 1,25 |  ![LINK](https://www.tinytronics.nl/shop/nl/mechanica-en-actuatoren/motoren/dc-motoren/kleine-dc-motor-3-6v)                                                                                           |
|5|              | Duracell      | Procell | Duracell Procell 9V Batterij      |  1x       | € 1,75 |  ![LINK](https://www.tinytronics.nl/shop/nl/power/batterijen/9v/duracell-industrial-9v-batterij)                                                                                                       |
|6|000512        | 9V-T-HARD     | Clip    | 9V Batterij clip                  |  1x       | € 0,50 |  ![LINK](https://www.tinytronics.nl/shop/nl/power/batterijhouders-en-clips/9v/9v-batterij-clip-met-losse-draden-15cm-t-hard)                                                                           |
|7|000318        |               | resistor| 220Ω weerstand                    |  1x       | € 0,05 |  ![LINK](https://www.tinytronics.nl/shop/nl/componenten/weerstanden/weerstanden/220%CF%89-weerstand-(led-voorschakelweerstand))                                                                        |
|8|              | Fairchild     | BC547   | BC547 Transistor                  |  1x       | € 0,11 |  ![LINK](https://www.bitsandparts.nl/Transistor-BC547-NPN-45V-0-1A-p115143)                                                                                                                            |
|9|HE0153-001    |               | I2C     | I2C LCD interface voor 16×2       |  1x       | € 1,95 |  ![LINK](https://www.hobbyelectronica.nl/product/i2c-lcd-interface-voor-16x2-en-20x4-displays/)                                                                                                        |
|*|HE0129-910    |               | button  | Push button                       |  1x       | € 0,20 |  ![LINK](https://www.hobbyelectronica.nl/product/push-button-6x6x5/?gclid=CjwKCAjwo8-SBhAlEiwAopc9W0U6wvlM5-_RB-9CSKUh7aWUpVVHtQ88qDtdZayypeZP-g7ha4PfExoCByYQAvD_BwE)                                 |
                                                                 

