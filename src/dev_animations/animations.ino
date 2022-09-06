#
# Copyright (c) 2022 by Andrzej Strzala aka Delight Technology. All Rights Reserved.
#

 #include <ezButton.h>
 #include <FastLED.h>

 // define the LEDs
 #define LED_PIN 2 //pin the LEDs are connected to
 #define NUM_LEDS 38
 #define MAX_BRIGHTNESS 30 //maximum brightness - useful if running off battery
 #define LED_TYPE WS2812B
 #define COLOR_ORDER GRB

 struct CRGB leds[NUM_LEDS];

 #define UPDATES_PER_SECOND 60

 int period = 5000;
 unsigned long time_now = 0;

 // define the buttons that we'll use.
 // one to control brightness and one to select palette.
 ezButton button(4);

 int paletteCounter = 0;
 boolean loopPalettes = 0;

 void setup() {
     delay(3000); // power-up safety delay - DO NOT REMOVE

     FastLED.addLeds < LED_TYPE, LED_PIN, COLOR_ORDER > (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
     FastLED.setBrightness(32); // start off 1/8 brightness
     FastLED.clear();

 }

 uint8_t gHue = 0; // rotating "base color" used by many of the patterns

 void loop() {

     button.loop(); // MUST call the loop() function first

     int btnState = button.getState();
     //Serial.println(btnState);

     switch (button.isPressed()) {
     case 1:
         paletteCounter++;
         loopPalettes = 0;
         if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
             paletteCounter = 0;
         }
         break;
     default:
         break;
     }

     EVERY_N_MILLISECONDS(30) {
         gHue++;
     } // slowly cycle the "base color" through the rainbow

     ChangePalettePeriodically();

     FastLED.show();
     FastLED.delay(1000 / UPDATES_PER_SECOND);
 }

 // There are several different palettes of colors demonstrated here.
 //
 // FastLED provides several 'preset' palettes: RainbowColors_p, RainbowStripeColors_p,
 // OceanColors_p, CloudColors_p, LavaColors_p, ForestColors_p, and PartyColors_p.
 //
 // Additionally, you can manually define your own color palettes, or you can write
 // code that creates color palettes on the fly.  All are shown here.

void ChangePalettePeriodically()
{    
    if( paletteCounter == 0)   {rainbow();}
    if( paletteCounter == 1)   {rainbowWithGlitter(); }
    if( paletteCounter == 2)   {Glitter(); }
    if( paletteCounter == 3)   {confetti(); }
    if( paletteCounter == 4)   {meteorRed(); }
    if( paletteCounter == 5)   {meteorLightBlue(); }
    if( paletteCounter == 6)   {meteorRainbow(); }
    if( paletteCounter == 7)   {anotherRainbow(); }
    if( paletteCounter == 8)   {rainbowBeat();}
    if( paletteCounter == 9)   {RedWhiteBlue();}
    if( paletteCounter == 10)  {LimeTurquoiseYellow();}
    if( paletteCounter == 11)  {RainbowThreeDots();}
    if( paletteCounter == 12)  {movingDots();}
    if( paletteCounter == 13)  {Lava();}
    if( paletteCounter == 14)  {NoiseBlueGreen();}
    if( paletteCounter == 15)  {loopThrough();}

}

 void rainbow() {
     // FastLED's built-in rainbow generator
     fill_rainbow(leds, NUM_LEDS, gHue, 7);
     Serial.println(loopPalettes);
     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }

 }

 void rainbowWithGlitter() {
     // built-in FastLED rainbow, plus some random sparkly glitter
     rainbow();
     addGlitter(80);
     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void addGlitter(fract8 chanceOfGlitter) {
     if (random8() < chanceOfGlitter) {
         leds[random16(NUM_LEDS)] += CRGB::White;
     }
 }

 void Glitter() {
     if (random8() < 80) {
         leds[random16(NUM_LEDS)] += CRGB::White;
     }
     fadeToBlackBy(leds, NUM_LEDS, 30);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void confetti() {
     // random colored speckles that blink in and fade smoothly
     fadeToBlackBy(leds, NUM_LEDS, 35);
     int pos = random16(NUM_LEDS);
     leds[pos] += CHSV(gHue + random8(64), 200, 255);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }

 }

 void meteorRed() {
     fadeToBlackBy(leds, NUM_LEDS, 15); // Smaller value = longer tail
     int i = (millis() / 40) % NUM_LEDS; // How fast it goes.
     leds[i] = CRGB::Red;
     //leds[i-1] = CRGB::Red;

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }

 }

 void meteorLightBlue() {
     fadeToBlackBy(leds, NUM_LEDS, 15); // Smaller value = longer tail
     int i = (millis() / 40) % NUM_LEDS; // How fast it goes.
     leds[i] = 0xE0FFFF;
     //leds[i-1] = CRGB::Red;

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void meteorRainbow() {
     // Smaller value = longer tail
     int i = (millis() / 40) % NUM_LEDS; // How fast it goes.
     leds[i] = CHSV((millis() / 20) - (i * 3), 255, 255);
     //leds[i-1] = CRGB::Red;
     fadeToBlackBy(leds, NUM_LEDS, 15);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void anotherRainbow() {
     // the moving rainbow
     for (uint16_t i = 0; i < NUM_LEDS; i++) {
         leds[i] = CHSV((millis() / 20) - (i * 3), 255, 255);
     }

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void rainbowBeat() {

     uint16_t beatA = beatsin16(30, 0, 255);
     uint16_t beatB = beatsin16(20, 0, 255);
     fill_rainbow(leds, NUM_LEDS, (beatA + beatB) / 2, 8);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void RedWhiteBlue() {

     uint16_t sinBeat = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
     uint16_t sinBeat2 = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
     uint16_t sinBeat3 = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

     leds[sinBeat] = CRGB::Aqua;
     leds[sinBeat2] = CRGB::BlueViolet;
     leds[sinBeat3] = CRGB::DeepPink;

     fadeToBlackBy(leds, NUM_LEDS, 25);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void LimeTurquoiseYellow() {

     uint16_t sinBeat = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
     uint16_t sinBeat2 = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
     uint16_t sinBeat3 = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

     leds[sinBeat] = CRGB::Lime;
     leds[sinBeat2] = CRGB::Maroon;
     leds[sinBeat3] = CRGB::Yellow;

     fadeToBlackBy(leds, NUM_LEDS, 25);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void RainbowThreeDots() {

     uint16_t sinBeat = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
     uint16_t sinBeat2 = beatsin16(30, 0, NUM_LEDS - 1, 0, 21845);
     uint16_t sinBeat3 = beatsin16(30, 0, NUM_LEDS - 1, 0, 43690);

     leds[sinBeat] = CHSV((millis() / 20) - (sinBeat * 3), 255, 255);
     leds[sinBeat2] = CHSV((millis() / 20) - (sinBeat2 * 3), 255, 255);
     leds[sinBeat3] = CHSV((millis() / 20) - (sinBeat3 * 3), 255, 255);

     fadeToBlackBy(leds, NUM_LEDS, 25);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void movingDots() {

     uint16_t posBeat = beatsin16(30, 0, NUM_LEDS - 1, 0, 0);
     uint16_t posBeat2 = beatsin16(60, 0, NUM_LEDS - 1, 0, 0);

     uint16_t posBeat3 = beatsin16(30, 0, NUM_LEDS - 1, 0, 32767);
     uint16_t posBeat4 = beatsin16(60, 0, NUM_LEDS - 1, 0, 32767);

     // Wave for LED color
     uint8_t colBeat = beatsin8(45, 0, 255, 0, 0);

     leds[(posBeat + posBeat2) / 2] = CHSV(colBeat, 255, 255);
     leds[(posBeat3 + posBeat4) / 2] = CHSV(colBeat, 255, 255);

     fadeToBlackBy(leds, NUM_LEDS, 15);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 CRGBPalette16 lavaPalette = CRGBPalette16(
     CRGB::DarkRed, CRGB::Maroon, CRGB::DarkRed, CRGB::Maroon,
     CRGB::DarkRed, CRGB::Maroon, CRGB::DarkRed, CRGB::DarkRed,
     CRGB::DarkRed, CRGB::DarkRed, CRGB::Red, CRGB::Orange,
     CRGB::White, CRGB::Orange, CRGB::Red, CRGB::DarkRed
 );

 void Lava() {
     for (int i = 0; i < NUM_LEDS; i++) {
         uint8_t brightness = inoise8(i * MAX_BRIGHTNESS, millis() / 5);
         uint8_t index = inoise8(i * 100, millis() / 10);
         leds[i] = ColorFromPalette(lavaPalette, index, brightness);
         //leds[i] = CHSV(0, 255, brightness);
     }

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
 }

 void NoiseBlueGreen() {

     uint8_t octaves = 1;
     uint16_t x = 0;
     int scale = 100;
     uint8_t hue_octaves = 1;
     uint16_t hue_x = 1;
     int hue_scale = 50;
     uint16_t ntime = millis() / 3;
     uint8_t hue_shift = 5;

     fill_noise16(leds, NUM_LEDS, octaves, x, scale, hue_octaves, hue_x, hue_scale, ntime, hue_shift);

     if (loopPalettes == 1) {
         if (millis() >= time_now + period) {
             time_now += period;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }

 }

 void loopThrough() {
     if (loopPalettes == 0) {
         fadeToBlackBy(leds, NUM_LEDS, 5);

         if (millis() >= time_now + period) {
             time_now += period;
             loopPalettes = 1;
             paletteCounter++;
             if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
                 paletteCounter = 0;
             }
         }
     }
     if (loopPalettes == 1) {
         paletteCounter++;
         if (paletteCounter > 15) { // adjust if you have more or less than 34 palettes
             paletteCounter = 0;
         }
     }
 }
