#pragma once

#include "patternsmatrix.h"

void renderBeatRainbow()
{
    uint8_t *bands = barHeights;
    uint8_t *peaks = peak;
    int peakBandIndex = _peakMaxIndex;
    int peakBandValue = peaks[peakBandIndex];
    static int beatCount = 0;

    bool beatDetected = false;
    bool clapsDetected = false;
    // beat detection
    if (peaks[0] == bands[0] && peaks[0] > 0) // new peak for bass must be a beat
    {
        beatCount++;
        beatDetected = true;
    }
    if (peakBandIndex >= BANDS_NUMBER / 2 && peakBandValue > 0)
    {
        clapsDetected = true;
    }

    for (int i = 0; i < STRIPE_SIZE; i++)
    {
        stripe[i] = blend(stripe[i], CRGB(0, 0, 0), 100); // fade to black over time

        // bass/beat = rainbow
        if (beatDetected)
        {
            if (random(0, 10 - ((float)peaks[1] / (float)255 * 10.0)) == 0)
            {
                stripe[i] = CHSV((beatCount * 10) % 255, 255, 255);
            }
        }

        // claps/highs = white twinkles
        if (clapsDetected)
        {
            if (random(0, 40 - ((float)peakBandIndex / (float)BANDS_NUMBER * 10.0)) == 0)
            {
                stripe[i] = CRGB(255, 255, 255);
            }
        }
    }
}
int vuMeterPeakMax;
void renderBasicTest()
{
    uint8_t *bands = barHeights;
    uint8_t *peaks = peak;
    int peakBandIndex = _peakMaxIndex;
    int peakBandValue = peaks[peakBandIndex];
    int vuMeter = volumeUnit;
    int vuMeterPeak = volumeUnitPeak;
    if (vuMeterPeakMax < volumeUnitPeak)
        vuMeterPeakMax = volumeUnitPeak;

    stripe[BANDS_NUMBER] = CRGB(0, 0, 0);

    // equilizer first BANDS_NUMBER
    for (int i = 0; i < BANDS_NUMBER; i++)
    {
        stripe[i] = CHSV(i * (200 / BANDS_NUMBER), 255, (int)peaks[i]);
    }

    // volume unit meter rest of stripe
    uint8_t vuLed = (uint8_t)map(vuMeter, 0, vuMeterPeakMax, BANDS_NUMBER + 1, STRIPE_SIZE - 1);
    uint8_t vuLedPeak = (uint8_t)map(vuMeterPeak, 0, vuMeterPeakMax, BANDS_NUMBER + 1, STRIPE_SIZE - 1);
    for (int i = BANDS_NUMBER + 1; i < STRIPE_SIZE; i++)
    {
        stripe[i] = CRGB(0, 0, 0);
        if (i < vuLed)
        {
            stripe[i] = i > (STRIPE_SIZE - ((STRIPE_SIZE - BANDS_NUMBER) * 0.2)) ? CRGB(50, 0, 0) : CRGB(0, 50, 0);
        }
        if (i == vuLedPeak)
        {
            stripe[i] = CRGB(50, 50, 50);
        }
    }
}

void renderBasicTest2()
{
    uint8_t *bands = barHeights;

    int peakBandIndex = _peakMaxIndex;
    int peakBandValue = peak[peakBandIndex];
    int vuMeter = volumeUnit;
    int vuMeterPeak = volumeUnitPeak;
    if (vuMeterPeakMax < volumeUnitPeak)
        vuMeterPeakMax = volumeUnitPeak;

    stripe[BANDS_NUMBER] = CRGB(0, 0, 0);

    // equilizer first BANDS_NUMBER
    uint8_t sss = 0;
    for (int i = 0; i < STRIPE_SIZE; i++)
    {
        sss++;
        if (sss >= BANDS_NUMBER)
        {
            sss = 0;
        }
        // Serial.print(" |s:");
        // Serial.print(sss);
        // Serial.print(" p:");
        // Serial.print(peak[sss]);
        // Serial.print(" i:");
        // Serial.print(i);
        // Serial.print("| ");
        stripe[i] = CHSV(i * (200 / (sss + 1)), 255, (int)peak[sss] * 5);
    }
    // Serial.println();
    // Serial.println();
    // delay(1000);
    // // volume unit meter rest of stripe
    // uint8_t vuLed = (uint8_t)map(vuMeter, 0, vuMeterPeakMax, BANDS_NUMBER + 1, STRIPE_SIZE - 1);
    // uint8_t vuLedPeak = (uint8_t)map(vuMeterPeak, 0, vuMeterPeakMax, BANDS_NUMBER + 1, STRIPE_SIZE - 1);
    // for (int i = BANDS_NUMBER + 1; i < STRIPE_SIZE; i++)
    // {
    //   stripe[i] = CRGB(0, 0, 0);
    //   if (i < vuLed)
    //   {
    //     stripe[i] = i > (STRIPE_SIZE - ((STRIPE_SIZE - BANDS_NUMBER) * 0.2)) ? CRGB(50, 0, 0) : CRGB(0, 50, 0);
    //   }
    //   if (i == vuLedPeak)
    //   {
    //     stripe[i] = CRGB(50, 50, 50);
    //   }
    // }
}
void loopPatternStripe()
{
    loopPatternMatrix();
    renderBasicTest2();
}

void setupPatternStripe()
{
    setupPatternMatrix();
}