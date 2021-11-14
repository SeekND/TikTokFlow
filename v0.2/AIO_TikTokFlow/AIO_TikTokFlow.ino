#include "FastLED.h"


////////////////////////////////// user can change and should

#define NUM_LEDS 16 // number of leds per circle (need to be all the same number for each of the circles you have

uint32_t systemruntime = 20; // how many seconds before next sequence
uint32_t flashtime = 3; // led flash time at the end of the sequence

///////////////////////////////// leave the rest alone unless you know what you are doing


////////////////////////////////////////////////////////////////// LEDS

uint32_t BRIGHTNESS =  200;
#define LED_PINA1 2
#define LED_PINA2 3
#define LED_PINA3 5

#define LED_PINB1 7
#define LED_PINB2 8
#define LED_PINB3 9

#define LED_PINC1 10
#define LED_PINC2 11
#define LED_PINC3 12

CRGB ledsA1[NUM_LEDS];
CRGB ledsA2[NUM_LEDS];
CRGB ledsA3[NUM_LEDS];

CRGB ledsB1[NUM_LEDS];
CRGB ledsB2[NUM_LEDS];
CRGB ledsB3[NUM_LEDS];

CRGB ledsC1[NUM_LEDS];
CRGB ledsC2[NUM_LEDS];
CRGB ledsC3[NUM_LEDS];


bool ledsonA = false;
bool ledsonB = false;
bool ledsonC = false;


uint32_t nexttimeA;
uint32_t nexttimeB;
uint32_t nexttimeC;
uint32_t waitingtime = flashtime * 1000;  // time between flashes in milliseconds
uint32_t runtime = systemruntime * 1000;  // time between flashes in milliseconds
uint32_t nextsequenceA;
uint32_t nextsequenceB;
uint32_t nextsequenceC;
uint32_t sequencechecker = 0;

int numberofsequences = 5;
int prewhosit = 0;
int whosit;

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<WS2812, LED_PINA1, RGB>(ledsA1, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PINA2, RGB>(ledsA2, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PINA3, RGB>(ledsA3, NUM_LEDS);   // prev brg

  FastLED.addLeds<WS2812, LED_PINB1, RGB>(ledsB1, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PINB2, RGB>(ledsB2, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PINB3, RGB>(ledsB3, NUM_LEDS);   // prev brg

  FastLED.addLeds<WS2812, LED_PINC1, RGB>(ledsC1, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PINC2, RGB>(ledsC2, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PINC3, RGB>(ledsC3, NUM_LEDS);   // prev brg


  //grb before
  FastLED.setBrightness( BRIGHTNESS );

  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    ledsA1[whiteLed] = CRGB::Green;
    ledsA2[whiteLed] = CRGB::Green;
    ledsA3[whiteLed] = CRGB::Green;

    ledsB1[whiteLed] = CRGB::Green;
    ledsB2[whiteLed] = CRGB::Green;
    ledsB3[whiteLed] = CRGB::Green;

    ledsC1[whiteLed] = CRGB::Green;
    ledsC2[whiteLed] = CRGB::Green;
    ledsC3[whiteLed] = CRGB::Green;
    FastLED.show();
  }

  delay(200);
  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    ledsA1[whiteLed] = CRGB::Black;
    ledsA2[whiteLed] = CRGB::Black;
    ledsA3[whiteLed] = CRGB::Black;

    ledsB1[whiteLed] = CRGB::Black;
    ledsB2[whiteLed] = CRGB::Black;
    ledsB3[whiteLed] = CRGB::Black;

    ledsC1[whiteLed] = CRGB::Black;
    ledsC2[whiteLed] = CRGB::Black;
    ledsC3[whiteLed] = CRGB::Black;
    FastLED.show();
  }

  nextsequenceA = millis();
  nextsequenceB = millis();
  nextsequenceC = millis();
  //sequencechecker = millis();

  Serial.println("Starting");
}

void loop() {

  if (millis() > sequencechecker + runtime + waitingtime || sequencechecker == 0 )
  {
    whosit = random(1, numberofsequences);

    if ( whosit == prewhosit ) {
      if ( whosit == numberofsequences )
      {
        whosit -= 1;
      }
      else if ( whosit == 1 )
      {
        whosit += 1;
      }
      else
      {
        int randi = random(0, 1);
        if (randi == 0)
          whosit += 1;
        else
          whosit -= 1;
      }
    }
    prewhosit = whosit;

    sequencechecker = millis();
    alloffA();
    alloffB();
    alloffC();

  }
  else {
    if (whosit == 1) {
      seq_left();

      Serial.println("Left");
    }
    else if (whosit == 2) {
      seq_middle();
      Serial.println("middle");
    }
    else if (whosit == 3) {
      seq_right();
      Serial.println("right");
    }
    else if (whosit == 4) {
      seq_leftright();
      Serial.println("across1");
    }
    else if (whosit == 5) {
      seq_rightleft();
      Serial.println("across2");
    }
  }
}


////////////////////////////////////////// FIRST UNIT

void ledgreenA1()
{
  if (millis() > nextsequenceA + runtime + waitingtime )
  {
    nextsequenceA = millis();
    ledsonA = false;
    Serial.println("Leds off");
  }
  else if (millis() > nextsequenceA + runtime )
  {
    if ( millis() + waitingtime > nexttimeA && !ledsonA ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsA1[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      Serial.println("Leds flashing");
      nexttimeA = millis();
      ledsonA = true;
    }
    else if ( millis() + waitingtime > nexttimeA && ledsonA ) {

      alloffA();
      nexttimeA = millis();
      ledsonA = false;
    }

  }
  else if (millis() > nextsequenceA ) {
    if (ledsonA == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsA1[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonA = true;

      Serial.println("Leds on");
    }
  }
}


void ledgreenA2()
{
  if (millis() > nextsequenceA + runtime + waitingtime )
  {
    nextsequenceA = millis();
    ledsonA = false;
  }
  else if (millis() > nextsequenceA + runtime )
  {
    if ( millis() + waitingtime > nexttimeA && !ledsonA ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsA2[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeA = millis();
      ledsonA = true;
    }
    else if ( millis() + waitingtime > nexttimeA && ledsonA ) {

      alloffA();
      nexttimeA = millis();
      ledsonA = false;
    }
  }
  else if (millis() > nextsequenceA ) {
    if (ledsonA == false ) {

      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsA2[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonA = true;
    }
  }
}

void ledgreenA3()
{
  if (millis() > nextsequenceA + runtime + waitingtime )
  {
    nextsequenceA = millis();
    ledsonA = false;
  }
  else if (millis() > nextsequenceA + runtime )
  {
    if ( millis() + waitingtime > nexttimeA && !ledsonA ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsA3[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeA = millis();
      ledsonA = true;
    }
    else if ( millis() + waitingtime > nexttimeA && ledsonA ) {

      alloffA();
      nexttimeA = millis();
      ledsonA = false;
    }
  }
  else if (millis() > nextsequenceA ) {
    if (ledsonA == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsA3[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonA = true;
    }
  }
}

void alloffA()
{
  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    ledsA1[whiteLed] = CRGB::Black;
    ledsA2[whiteLed] = CRGB::Black;
    ledsA3[whiteLed] = CRGB::Black;
    FastLED.show();
  }
}








////////////////////////////////////////// SECOND UNIT


void ledgreenB1()
{
  if (millis() > nextsequenceB + runtime + waitingtime )
  {
    nextsequenceB = millis();
    ledsonB = false;
  }
  else if (millis() > nextsequenceB + runtime )
  {
    if ( millis() + waitingtime > nexttimeB && !ledsonB ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsB1[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeB = millis();
      ledsonB = true;
    }
    else if ( millis() + waitingtime > nexttimeB && ledsonB ) {

      alloffB();
      nexttimeB = millis();
      ledsonB = false;
    }
  }
  else if (millis() > nextsequenceB ) {
    if (ledsonB == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsB1[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonB = true;
    }
  }
}


void ledgreenB2()
{
  if (millis() > nextsequenceB + runtime + waitingtime )
  {
    nextsequenceB = millis();
    ledsonB = false;
  }
  else if (millis() > nextsequenceB + runtime )
  {
    if ( millis() + waitingtime > nexttimeB && !ledsonB ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsB2[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeB = millis();
      ledsonB = true;
    }
    else if ( millis() + waitingtime > nexttimeB && ledsonB ) {

      alloffB();
      nexttimeB = millis();
      ledsonB = false;
    }
  }
  else if (millis() > nextsequenceB ) {
    if (ledsonB == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsB2[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonB = true;
    }
  }
}

void ledgreenB3()
{
  if (millis() > nextsequenceB + runtime + waitingtime )
  {
    nextsequenceB = millis();
    ledsonB = false;
  }
  else if (millis() > nextsequenceB + runtime )
  {
    if ( millis() + waitingtime > nexttimeB && !ledsonB ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsB3[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeB = millis();
      ledsonB = true;
    }
    else if ( millis() + waitingtime > nexttimeB && ledsonB ) {

      alloffB();
      nexttimeB = millis();
      ledsonB = false;
    }
  }
  else if (millis() > nextsequenceB ) {
    if (ledsonB == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsB3[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonB = true;
    }
  }
}

void alloffB()
{
  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    ledsB1[whiteLed] = CRGB::Black;
    ledsB2[whiteLed] = CRGB::Black;
    ledsB3[whiteLed] = CRGB::Black;
    FastLED.show();
  }
}









////////////////////////////////////////// THIRD UNIT


void ledgreenC1()
{
  if (millis() > nextsequenceC + runtime + waitingtime )
  {
    nextsequenceC = millis();
    ledsonC = false;
  }
  else if (millis() > nextsequenceC + runtime )
  {
    if ( millis() + waitingtime > nexttimeC && !ledsonC ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsC1[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeC = millis();
      ledsonC = true;
    }
    else if ( millis() + waitingtime > nexttimeC && ledsonC ) {

      alloffC();
      nexttimeC = millis();
      ledsonC = false;
    }
  }
  else if (millis() > nextsequenceC ) {
    if (ledsonC == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsC1[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonC = true;
    }
  }
}


void ledgreenC2()
{
  if (millis() > nextsequenceC + runtime + waitingtime )
  {
    nextsequenceC = millis();
    ledsonC = false;
  }
  else if (millis() > nextsequenceC + runtime )
  {
    if ( millis() + waitingtime > nexttimeC && !ledsonC ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsC2[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeC = millis();
      ledsonC = true;
    }
    else if ( millis() + waitingtime > nexttimeC && ledsonC ) {

      alloffC();
      nexttimeC = millis();
      ledsonC = false;
    }
  }
  else if (millis() > nextsequenceC ) {
    if (ledsonC == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsC2[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonC = true;
    }
  }
}

void ledgreenC3()
{
  if (millis() > nextsequenceC + runtime + waitingtime )
  {
    nextsequenceC = millis();
    ledsonC = false;
  }
  else if (millis() > nextsequenceC + runtime )
  {
    if ( millis() + waitingtime > nexttimeC && !ledsonC ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsC3[whiteLed] = CRGB::Green;
        FastLED.show();
      }

      nexttimeC = millis();
      ledsonC = true;
    }
    else if ( millis() + waitingtime > nexttimeC && ledsonC ) {

      alloffC();
      nexttimeC = millis();
      ledsonC = false;
    }
  }
  else if (millis() > nextsequenceC ) {
    if (ledsonC == false ) {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        ledsC3[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      ledsonC = true;
    }
  }
}

void alloffC()
{
  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    ledsC1[whiteLed] = CRGB::Black;
    ledsC2[whiteLed] = CRGB::Black;
    ledsC3[whiteLed] = CRGB::Black;
    FastLED.show();
  }
}







//////////////////////// sequences


void seq_left() {
  ledgreenA1();
  ledgreenB1();
  ledgreenC1();
}

void seq_middle() {
  ledgreenA2();
  ledgreenB2();
  ledgreenC2();
}


void seq_right() {
  ledgreenA3();
  ledgreenB3();
  ledgreenC3();
}

void seq_leftright() {
  ledgreenA1();
  ledgreenB2();
  ledgreenC3();
}

void seq_rightleft() {
  ledgreenA3();
  ledgreenB2();
  ledgreenC1();
}
