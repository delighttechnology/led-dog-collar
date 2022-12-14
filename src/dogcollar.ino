#
# Copyright (c) 2022 by Andrzej Strzala aka Delight Technology. All Rights Reserved.
#

#include <EasyButton.h>
#include <FastLED.h>

#define LED_PIN 2 //pin the LEDs are connected to
#define KEEP_ALIVE 3
#define BUTTON_PIN 4
#define NUM_LEDS 37
#define MAX_BRIGHTNESS 30 //maximum brightness - useful if running off battery
#define UPDATES_PER_SECOND 60

#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

// define the buttons that we'll use.
// one to control brightness and one to select palette.
EasyButton button(BUTTON_PIN);

struct CRGB leds[NUM_LEDS];
int period = 30000;
unsigned long time_now = 0;

//variables to keep track of the animation order
int paletteCounter = 0;
boolean loopPalettes = 0;

//Change colours periodically
uint8_t gHue = 0;

void onPressedForDuration() {
    digitalWrite(KEEP_ALIVE, LOW);
    delay(20000);
}

void onPressedButton() {
    paletteCounter++;
    loopPalettes = 0;
    if (paletteCounter > 15) {
        paletteCounter = 0;
    }
    delay(100);
}

void setup() {
    pinMode(BUTTON_PIN, OUTPUT); // set the LED pin as an output
    pinMode(KEEP_ALIVE, OUTPUT);

    // Initialize the button.
    button.begin();
    // Add the callback function to be called when the button is pressed for at least the given time.

    button.onPressed(onPressedButton);
    button.onPressedFor(1000, onPressedForDuration);

    FastLED.addLeds < LED_TYPE, LED_PIN, COLOR_ORDER > (leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(MAX_BRIGHTNESS);
    FastLED.clear();
}

void loop() {

    // Keep alive the NPN
    digitalWrite(KEEP_ALIVE, HIGH);

    // Continuously read the status of the button.
    button.read();

    EVERY_N_MILLISECONDS(30) {
        gHue++;
    } // slowly cycle the "base color" through the rainbow

    ChangePalettePeriodically();

    FastLED.show();
    FastLED.delay(1000 / UPDATES_PER_SECOND);

}

void ChangePalettePeriodically()
{    
    if( paletteCounter == 0)   {rainbow();}
    if( paletteCounter == 1)   {rainbowWithglitter(); }
    if( paletteCounter == 2)   {glitter(); }
    if( paletteCounter == 3)   {confetti(); }
    if( paletteCounter == 4)   {meteorRed(); }
    if( paletteCounter == 5)   {meteorLightBlue(); }
    if( paletteCounter == 6)   {meteorRainbow(); }
    if( paletteCounter == 7)   {anotherRainbow(); }
    if( paletteCounter == 8)   {rainbowBeat();}
    if( paletteCounter == 9)   {redWhiteBlue();}
    if( paletteCounter == 10)  {limeTurquoiseYellow();}
    if( paletteCounter == 11)  {rainbowThreeDots();}
    if( paletteCounter == 12)  {movingDots();}
    if( paletteCounter == 13)  {lava();}
    if( paletteCounter == 14)  {noiseBlueGreen();}
    if( paletteCounter == 15)  {loopThrough();}

}


void rainbow() {
    // FastLED's built-in rainbow generator
    fill_rainbow(leds, NUM_LEDS, gHue, 7);
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

void rainbowWithglitter() {
    // built-in FastLED rainbow, plus some random sparkly glitter
    rainbow();
    addglitter(80);
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

void addglitter(fract8 chanceOfglitter) {
    if (random8() < chanceOfglitter) {
        leds[random16(NUM_LEDS)] += CRGB::White;
    }
}

void glitter() {
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

void redWhiteBlue() {

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

void limeTurquoiseYellow() {

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

void rainbowThreeDots() {

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

void lava() {
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

void noiseBlueGreen() {

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
