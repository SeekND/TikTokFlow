#include "FastLED.h"


////////////////////////////////// user can change and should

String tiktokname = "T1"; // T1 means the first tick tock flow array. T2 for the second, T3 third ...


#define NUM_LEDS 45 // number of leds per circle (need to be all the same number for each of the circles you have





///////////////////////////////// leave the rest alone unless you know what you are doing

const char TERMINATOR = '|';
bool flash1 = false;
bool flash2 = false;
bool flash3 = false;
bool ledson = false; // to allow the leds to flash without stopping the code

String firstled = tiktokname + "_1";
String secondled = tiktokname + "_2";
String thirdled = tiktokname + "_3";
String firstledF = tiktokname + "_1F";
String secondledF = tiktokname + "_2F";
String thirdledF = tiktokname + "_3F";

String c; // string you get from serial

////////////////////////////////////////////////////////////////// LEDS

uint32_t BRIGHTNESS =  200;
#define LED_PIN1 2
#define LED_PIN2 3
#define LED_PIN3 4

CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];


uint32_t nexttime;
uint32_t waitingtime = 300;    // time between flashes in milliseconds

void setup() {
  Serial.begin(9600);

  FastLED.addLeds<WS2812, LED_PIN1, GRB>(leds1, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PIN2, GRB>(leds2, NUM_LEDS);   // prev brg
  FastLED.addLeds<WS2812, LED_PIN3, GRB>(leds3, NUM_LEDS);   // prev brg
  FastLED.setBrightness( BRIGHTNESS );

  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds1[whiteLed] = CRGB::Green;
    leds2[whiteLed] = CRGB::Green;
    leds3[whiteLed] = CRGB::Green;
    FastLED.show();
  }

  delay(200);
  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds1[whiteLed] = CRGB::Black;
    leds2[whiteLed] = CRGB::Black;
    leds3[whiteLed] = CRGB::Black;
    FastLED.show();
  }

}

void loop() {

  if (Serial.available() > 0 )
  {
    c = Serial.readStringUntil(TERMINATOR);

    Serial.println(c);
    if ( c == firstled )
    {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        leds1[whiteLed] = CRGB::Green;
        leds2[whiteLed] = CRGB::Black;
        leds3[whiteLed] = CRGB::Black;
        FastLED.show();
      }
      flash1 = false;
      flash2 = false;
      flash3 = false;
      Serial.println("First led on");
    }

    else if ( c == secondled )
    {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        leds1[whiteLed] = CRGB::Black;
        leds2[whiteLed] = CRGB::Green;
        leds3[whiteLed] = CRGB::Black;
        FastLED.show();
      }
      flash1 = false;
      flash2 = false;
      flash3 = false;
    }

    else if ( c == thirdled )
    {
      for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
      {
        leds1[whiteLed] = CRGB::Black;
        leds2[whiteLed] = CRGB::Black;
        leds3[whiteLed] = CRGB::Green;
        FastLED.show();
      }
      flash1 = false;
      flash2 = false;
      flash3 = false;
    }
    else if ( c == firstledF )
    {
      flash1 = true;
    }
    else if ( c == secondledF )
    {
      flash2 = true;
    }
    else if ( c == thirdledF )
    {
      flash3 = true;
    }
  }

  if (flash1)
  {
    ledgreen1F();
  }
  if (flash2)
  {
    ledgreen2F();
  }

  if (flash3)
  {
    ledgreen3F();
  }
}


void ledgreen1F()
{
  if ( millis() + waitingtime > nexttime && !ledson ) {
    for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds1[whiteLed] = CRGB::Green;
      FastLED.show();
    }
    
    Serial.println("First led flashing");
    nexttime = millis();
    ledson = true;
  }
  else if ( millis() + waitingtime > nexttime && ledson ) {

    alloff();
    nexttime = millis();
    ledson = false;
  }

  //waitingtime = 300;

}

void ledgreen2F()
{
  if ( millis() + waitingtime > nexttime && !ledson ) {

    for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds2[whiteLed] = CRGB::Green;
      FastLED.show();
    }
    nexttime = millis();
    ledson = true;
  }

  else if ( millis() + waitingtime > nexttime && ledson ) {

    alloff();
    nexttime = millis();
    ledson = false;
  }

  //waitingtime = 300;
}


void ledgreen3F()
{
  if ( millis() + waitingtime > nexttime && !ledson ) {
    for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
    {
      leds3[whiteLed] = CRGB::Green;
      FastLED.show();
    }
    nexttime = millis();
    ledson = true;
  }

  else if ( millis() + waitingtime > nexttime && ledson ) {

    alloff();
    nexttime = millis();
    ledson = false;
  }

  //waitingtime = 300;
}


void alloff()
{
  for (byte whiteLed = 0; whiteLed < NUM_LEDS; whiteLed = whiteLed + 1)
  {
    leds1[whiteLed] = CRGB::Black;
    leds2[whiteLed] = CRGB::Black;
    leds3[whiteLed] = CRGB::Black;
    FastLED.show();
  }
}
