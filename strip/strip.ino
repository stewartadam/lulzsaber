// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include <math.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6
//#define BTNPIN         12

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60
#define NUMBEAM        8

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 3; // delay for half a second
int idx = 0;
int btnval = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code
  Serial.begin(9600);
  //  pinMode(BTNPIN, INPUT);
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  /*
      // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.
      int r = 0;
      int g = 0;
      int b = 0;
      for(int i=0;i<NUMPIXELS;i++){
      r = g = (b++%100);
      r = (r+2)%100;

      // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(r,g,b));
  */

  int mainR = 30;
  int brightR = 255;
  int off = 0;

  //  btnval = digitalRead(BTNPIN);

  for (int i = 0; i < NUMPIXELS - NUMBEAM; i++) {
    pixels.setPixelColor(i, pixels.Color(mainR, off, off));
  }
  for (int beam = 0; beam < NUMBEAM; ++beam) {
    pixels.setPixelColor(idx++, pixels.Color(brightR, off, off));
    idx = idx % NUMPIXELS;
  }
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
}

int rainbowInc = 0;
int rainbowMax = 32;

void fullRainbow(int pixIdx) {
  int r = Math.sin(0.3*rainbowInx + 0) * 127 + 128;
  int g = Math.sin(0.3*rainbowInx + 2) * 127 + 128;
  int b = Math.sin(0.3*rainbowInx + 4) * 127 + 128;

  pixels.setPixel(pixIdx, pixels.Color(r,g,b));
}
}

