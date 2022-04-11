# Blueprint technical Documentation

## Wiring diagram 
![Wiring diagram](IMG/wiring diagram.png)

## Bill of materials


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
                                                                 

## Hardware architecture Overview
![Hardware architecture Overview](IMG/IoT hardware architecture Overview.png)

## UML
![UML](IMG/IoT software UML.png)

## API documentation 

Used API-endpoint


Only the current weather data in the compact parameter:

```
GET http://api.iot.hva-robots.nl/weather/Amsterdam/compact
```

Sample response:

```
{
  "success": true,
  "data": {
    "FeelsLikeC": "11",
    "FeelsLikeF": "53",
    "cloudcover": "25",
    "humidity": "94",
    "localObsDateTime": "2021-09-22 08:53 AM",
    "observation_time": "06:53 AM",
    "precipInches": "0.0",
    "precipMM": "0.0",
    "pressure": "1028",
    "pressureInches": "30",
    "temp_C": "12",
    "temp_F": "54",
    "uvIndex": "1",
    "visibility": "9",
    "visibilityMiles": "5",
    "weatherCode": "116",
    "weatherDesc": [
      {
        "value": "Partly cloudy"
      }
    ],
    "weatherIconUrl": [
      {
        "value": ""
      }
    ],
    "winddir16Point": "SW",
    "winddirDegree": "220",
    "windspeedKmph": "15",
    "windspeedMiles": "9"
  }
}
```

The request of data is the equivalent to a regular call to create a post above:

| Field | Type   | Description                                                                                                    |
|:-----:|:------:| --------------------------------------------------------------------------------------------------------------:|
| API   | string | sends a formated string value between interfaces, values that are measurement of outdoor sensor of the weather |

The rules around publishing each request to this API must respect:

- This API is only use for creative goals and not for the purpose of making money.
- If the user is neither a writer nor an editor, the user is not allowed to create any posts in a publication.
- Don't use verbs in urls.

Possible Http code:

| Http code              | Description                                                                                                                                   |
|:----------------------:| ---------------------------------------------------------------------------------------------------------------------------------------------:|
| 307 Temporary Redirect | redirect status response code indicates that the resource requested has been temporarily moved to the URL given by the `Location` headers.    |
| 200 OK                 | success status response code indicates that the request has succeeded.                                                                        |
| 400 Bad Request        | response status code indicates that the server cannot or will not process the request due to something that is perceived to be a client error |


## System architecture 
![System architreture](IMG/IoT system architecture .png)