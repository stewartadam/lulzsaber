# What is this?
Lulzsaber is our ConUHacks hackathon project to get introduced to hardware hacking. We're embedding an Adafruit Flora Arduino board into a wooden sword with LEDs for use in a costume later this year.

# Instructions
## Arduino IDE setup
1. Download the [Arduino IDE](https://www.arduino.cc/en/Main/Software)
2. Open Arduino app
3. Go to *Preferences > Additional Board Manager URLs*, enter: https://adafruit.github.io/arduino-board-index/package_adafruit_index.json
4. *Tools > Port* and select the one with "usbmodem" in it
5. Go to *Tools > Boards > Boards Manager...*
6. Install "Adafruit AVR Boards" package
7. From *Tools > Board*, select Adafruit Flora
8. [Blink the LED!](https://learn.adafruit.com/getting-started-with-flora/blink-onboard-led)

## NeoPixel library setup
There's a [great PDF](https://learn.adafruit.com/downloads/pdf/adafruit-neopixel-uberguide.pdf) with lots of NeoPixel information. In short:
1. Install the "Adafruit NeoPixel" package
2. Code! (see page 15 & 17)
