#include <FastLED.h>
#include <LiquidCrystal.h>

const int NUM_LEDS = 18;//60;
const int DATA_PIN = 6;
const int CLOCK_PIN = 7;
const int phoPin1 = A0;
const int phoPin2 = A1;
const int phoPin3 = A2;

int photores1 = 0;
int photores2 = 0;
int photores3 = 0;
int threshold = 300;
int scored1 = 0;
int scored2 = 0;
int scored3 = 0;
int totalScore = 0;

CRGB leds[NUM_LEDS];
//LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

void setup() {

  Serial.begin(9600);
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, NUM_LEDS);

  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    FastLED.show();
  }

  //lcd.begin(16, 2);
  //lcd.clear();

}

void loop() {

  while(totalScore < 18) {
    photores1 = analogRead(phoPin1);
    photores2 = analogRead(phoPin2);
    photores3 = analogRead(phoPin3);

    //lcd.setCursor(0, 0);

    if (photores1 < threshold) {
      scored1 = 6; //20;
    }

    if (photores2 < threshold) {
      scored2 = 6; //20;
    }

    if (photores3 < threshold) {
      scored3 = 6; //20;
    }

    totalScore = scored1 + scored2 + scored3;

    //lcd.print(totalScore);

    /*if (scored1 || scored2 || scored3) {
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
        FastLED.show();
        delay(50);
      }
    }*/

    for (int i = 0; i < totalScore; i++) {
      leds[i] = CRGB::Green;
      FastLED.show();
      delay(10);
    }

    /*debugging
    Serial.println("Photo Resistor 1: " + photores1);
    Serial.println("Photo Resistor 2: " + photores2);
    Serial.println("Photo Resistor 3: " + photores3);

    Serial.println("First target score status: " + scored1);
    Serial.println("Second target score status: " + scored2);
    Serial.println("Third target score status: " + scored3);
  */
    Serial.println(totalScore);
    delay(20);
  }

  photores1 = analogRead(phoPin1);
  photores2 = analogRead(phoPin2);
  photores3 = analogRead(phoPin3);

  if (photores1 >= threshold && photores2 >= threshold && photores3 >= threshold) {
    FastLED.clear(true);
    scored1 = 0;
    scored2 = 0;
    scored3 = 0;
    totalScore = 0;
    photores1 = 0;
    photores2 = 0;
    photores3 = 0;
  }

  delay(2000);

  Serial.println(totalScore);
  

}