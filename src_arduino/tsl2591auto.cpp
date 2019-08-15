// NOLINT(legal/copyright)
/******************************************************************************

    auto-gain implementation for TSL2591 Digital Light Sensor

    libraries used:
        ~ Adafruit_TSL2591
            written by KT0WN (adafruit.com),
            Copyright (c) 2014 Adafruit Industries
            license: BSD

    written by stefan krueger (s-light),
        git@s-light.eu, http://s-light.eu, https://github.com/s-light/

******************************************************************************/
/******************************************************************************
The MIT License (MIT)

Copyright (c) 2019 Stefan Krüger

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
******************************************************************************/


// include own headerfile
// NOLINTNEXTLINE(build/include)
#include "./tsl2591auto.h"


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// main api

slight_TSL2591Auto::slight_TSL2591Auto() {
    ready = false;
}

slight_TSL2591Auto::~slight_TSL2591Auto() {
    end();
}

void slight_TSL2591Auto::begin(Stream &out) {
    // clean up..
    end();
    // start up...
    if (ready == false) {
        // setup
        if (tsl.begin()) {
            out.println(F("found TSL2591 sensor"));

            // 1x gain (bright light)
            // tsl.setGain(TSL2591_GAIN_LOW);
            // 25x gain
            tsl.setGain(TSL2591_GAIN_MED);
            // 428x gain
            // tsl.setGain(TSL2591_GAIN_HIGH);

            // shortest integration time for bright light
            // longest integration time for low light
            // tsl.setTiming(TSL2591_INTEGRATIONTIME_100MS);
            // tsl.setTiming(TSL2591_INTEGRATIONTIME_200MS);
            tsl.setTiming(TSL2591_INTEGRATIONTIME_300MS);
            // tsl.setTiming(TSL2591_INTEGRATIONTIME_400MS);
            // tsl.setTiming(TSL2591_INTEGRATIONTIME_500MS);
            // tsl.setTiming(TSL2591_INTEGRATIONTIME_600MS);

            tsl_print_details(out);

            tsl.enable();

            // enable
            ready = true;
        } else {
            out.println(F("no sensor found ... check your wiring?"));
            ready = false;
        }
    }
}

void slight_TSL2591Auto::end() {
    if (ready) {
        // nothing to do..
    }
}

void slight_TSL2591Auto::update() {
    if (ready) {
        // do it :-)
    }
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// custom tsl functions

uint8_t slight_TSL2591Auto::tsl_read8(uint8_t reg) {
    uint8_t x;

    Wire.beginTransmission(TSL2591_ADDR);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(TSL2591_ADDR, 1);
    x = Wire.read();

    return x;
}

uint16_t slight_TSL2591Auto::tsl_read16(uint8_t reg) {
    uint16_t x;
    uint16_t t;

    Wire.beginTransmission(TSL2591_ADDR);
    Wire.write(reg);
    Wire.endTransmission();

    Wire.requestFrom(TSL2591_ADDR, 2);
    t = Wire.read();
    x = Wire.read();

    x <<= 8;
    x |= t;
    return x;
}

void slight_TSL2591Auto::tsl_write8(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(TSL2591_ADDR);
    Wire.write(reg);
    Wire.write(value);
    Wire.endTransmission();
}

void slight_TSL2591Auto::tsl_write8(uint8_t reg) {
    Wire.beginTransmission(TSL2591_ADDR);
    Wire.write(reg);
    Wire.endTransmission();
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// helper

void slight_TSL2591Auto::tsl_print_details(Print &out) {
    sensor_t sensor;
    tsl.getSensor(&sensor);
    out.println(F("------------------------------------"));
    out.print(F("Sensor:     "));
    out.println(sensor.name);
    out.print(F("Driver Ver: "));
    out.println(sensor.version);
    out.print(F("Unique ID:  "));
    out.println(sensor.sensor_id);
    out.print(F("Max Value:  "));
    out.print(sensor.max_value);
    out.println(F(" lux"));
    out.print(F("Min Value:  "));
    out.print(sensor.min_value);
    out.println(F(" lux"));
    out.print(F("Resolution: "));
    out.print(sensor.resolution, 4);
    out.println(F(" lux"));
    out.println(F("------------------------------------"));
    out.print(F("Gain:         "));
    tsl.printGain(out);
    out.println();
    out.print(F("Timing:       "));
    out.print(tsl.getTimingInMS());
    out.println(" ms");
    out.println(F("------------------------------------"));
    out.println(F(""));
}


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THE END
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
