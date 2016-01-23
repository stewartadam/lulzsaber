/*
   Play example using Time3 library.

   The sample must be raw 8bits 8KHz, please read README.md.

    Juan J. Martinez <jjm@usebox.net>
    https://github.com/reidrac/play-pcm-example
*/

#include <avr/pgmspace.h>
#include <TimerThree.h>

// http://playground.arduino.cc/Main/Printf
#include <stdarg.h>
void p(char *fmt, ... ) {
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt );
  vsnprintf(buf, 128, fmt, args);
  va_end (args);
  Serial.print(buf);
}
void p(const __FlashStringHelper *fmt, ... ) {
  char buf[128]; // resulting string limited to 128 chars
  va_list args;
  va_start (args, fmt);
#ifdef __AVR__
  vsnprintf_P(buf, sizeof(buf), (const char *)fmt, args); // progmem for AVR
#else
  vsnprintf(buf, sizeof(buf), (const char *)fmt, args); // for the rest of the world
#endif
  va_end(args);
  Serial.print(buf);
}

/* sample to play */
#include "coin8.h"

volatile unsigned char *play_sample;
volatile unsigned short play_sample_length;
volatile unsigned short play_sample_ptr;
volatile int play_pin;

const unsigned int PWM_HIGH = 1023;
const unsigned int SAMPLE_SIZE = 255;
unsigned int iteration = 0;
// 8KHz are 125 microsenconds
int hz = 8000;
int microsec = 1000000;
int pulsewidth = microsec / hz;

/* for Teensy 2.0: pin 9 */
void init_play(unsigned char pin)
{
  play_sample_length = 0;
  play_pin = pin;

  pinMode(play_pin, OUTPUT);
  Timer3.initialize(pulsewidth);
  Timer3.attachInterrupt(play_cb);
  Timer3.pwm(pin, PWM_HIGH);
}

void play_cb(void)
{
  if (play_sample_length)
  {
    float abyte = pgm_read_byte(&play_sample[play_sample_ptr]);
    //Timer3.setPwmDuty(play_pin, abyte/SAMPLE_SIZE*PWM_HIGH);

    digitalWrite(play_pin, HIGH);
    delayMicroseconds(abyte/SAMPLE_SIZE*pulsewidth);
    digitalWrite(play_pin, LOW);
    delayMicroseconds(pulsewidth - abyte/SAMPLE_SIZE*pulsewidth);

    play_sample_ptr++;
    if (play_sample_ptr == play_sample_length)
    {
      play_sample_length = 0;
      Timer3.setPwmDuty(play_pin, 0);
    }
    iteration = (iteration + 1) % 10000;
  }
}

void play(const unsigned char *sample, const unsigned short length)
{
  iteration = 0;
  noInterrupts();
  play_sample = (unsigned char *)sample;
  play_sample_ptr = 0;
  play_sample_length = length;
  interrupts();
}

void setup()
{
  Serial.begin(9600);
  delayMicroseconds(1000000);
  init_play(9);
  play(coin8, coin8_len);
}

void loop()
{
  /* Do nothing */
}

/* EOF */
