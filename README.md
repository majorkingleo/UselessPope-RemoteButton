# UselessPope-RemoteButton

## Hardware
* AZ-Delivery ESP32 Dev Kit V4 ESO32-WROOM-32 

## IDE
* Arduino 2.3.5
* Additional Board Manager Urls: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
* Selected Board: uPesy ESP32 Wroom DevKit

# What it does
* There is Button that can be pushed, this action will send a UDB message via WLAN to the connected network.
* The server can send a message how the NEO Pixel LED should blink.

# GPIOs
* GPIO32 NeoPixel PWM 1
* GPIO33 NeoPixel PWM 2
* GPIO25 NeoPixel PWM 3
* GPIO3 Button

# Debug Port
* 115200 baud rate
* 
