// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#include <math.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6
#define BTNPIN         10

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60
#define BEAM_LENGTH    15
#define BRIGHT_R       200
#define MAIN_R         30
#define OFF            0

int rainbowInc = 0;
int rainbowMax = 32;

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 10; // delay for half a second
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

  btnval = digitalRead(BTNPIN);
  Serial.print(btnval);
  Serial.print("\n");
  if (btnval == HIGH) {
    displayMain();
    displayBeam();
  }
  else{
    for(int i=0;i<NUMPIXELS;i++){
     // fullRainbow(i);
     pixels.setPixelColor(i,pixels.Color(0,0,0));
    }
    
  }

  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(delayval); // Delay for a period of time (in milliseconds).
}

void displayMain() {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(MAIN_R, OFF, OFF));
  }
}

void displayBeam() {
  for (int beam_step = 0; beam_step < BEAM_LENGTH; ++beam_step) {
    int brightR = percent(BRIGHT_R, beam_step, BEAM_LENGTH);
    int pos = (idx + beam_step) % NUMPIXELS;
    pixels.setPixelColor(pos, pixels.Color(brightR, OFF, OFF));
  }
  idx = (idx + 1) % NUMPIXELS;
}

bool inRange(int value, int st, int en) {
  if (en < st) {
    return (value >= st) || (value <= en);
  } else {
    return (value >= st) && (value <= en);
  }
}

int percent(int value, int percent, int totalPercent) {
  int temp = (int) (value * (percent * 1.0 / totalPercent));
  temp += 255 - BRIGHT_R;
  return temp;
}

void fullRainbow(int pixIdx) {
  int r = sin(0.3 * rainbowInc + 0) * 127 + 128;
  int g = sin(0.3 * rainbowInc + 2) * 127 + 128;
  int b = sin(0.3 * rainbowInc + 4) * 127 + 128;

  pixels.setPixelColor(pixIdx, pixels.Color(r, g, b));

  rainbowInc = (rainbowInc++) % rainbowMax;
}
