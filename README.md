# ESP8266-RaspberryPi-MQTT-NodeRED
ESP8266 MQTT Sensors to Raspberry Pi dashboard using NodeRED

I built a dashboard with a Raspberry Pi to display sensors data. The Raspberry Pi has a screen. The dashboard is powered by Node-RED and displayed on Chromium in Kiosk node.
The Raspberry Pi is setup as a WiFi access point so that the ESP8266 sensors can communicate directly to the Raspberry Pi through WiFi in MQTT.

<img src="https://github.com/DavidPetit/ESP8266-RaspberryPi-MQTT-NodeRED/blob/master/raspberrypi.jpg" width="300">

<img src="https://github.com/DavidPetit/ESP8266-RaspberryPi-MQTT-NodeRED/blob/master/esp8266_sensor.jpg" width="300">

## Requirements

### Hardware
* At least one ESP8266 board (I am using Wemos D1 Mini)
* At least one sensor connected to a ESP8266 board (I am using Wemos SHT30 shield)
* One Raspberry Pi (model 3 is prefered)
* A LCD screen for the Raspberry Pi (I am using a 3.5 Inches LCD touch screen)
* A computer to do the setup on Rapsberry Pi and on the ESP8266 boards

### Software
#### For ESP8266 boards
* Program like the in .ino from this repo to flash on ESP8266
#### For Rapsberry Pi
* Raspbian (https://www.raspberrypi.org/downloads/raspbian/)
* MQTT Broker (I use Mosquitto: https://mosquitto.org/download/)
* Node-RED (https://nodered.org/)
#### For developement computer
* Arduino IDE (on computer for ESP8266 development and being able to flash programs on the boards)
