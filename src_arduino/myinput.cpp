// NOLINT(legal/copyright)

/******************************************************************************

    __doc__ = """
    sensor input and pre-conditioning
    """

    libraries used:
        ~ Adafruit_Sensor
        ~ Adafruit_TSL2591
            written by Adafruit
        ~ slight_ButtonInput
        ~ slight_DebugMenu
            written by stefan krueger (s-light),
                github@s-light.eu, http://s-light.eu, https://github.com/s-light/
            license: MIT

    written by stefan krueger (s-light),
        github@s-light.eu, http://s-light.eu, https://github.com/s-light/

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

// cpplint
// disable linting for next line:
// NOLINTNEXTLINE(readability/nolint)
// https://github.com/google/styleguide/blob/gh-pages/cpplint/cpplint.py

// include own headerfile
// NOLINTNEXTLINE(build/include)
#include "./myinput.h"

// // include Core Arduino functionality
// #include <Arduino.h>
//
// #include <slight_DebugMenu.h>
//
// #include <Wire.h>
// #include <Adafruit_Sensor.h>
// #include "Adafruit_TSL2591.h"
//
// #include <slight_ButtonInput.h>


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// functions

// MyInput::MyInput(button):
// ) {

MyInput::MyInput(
    MyAnimation &animation
):
    animation(animation),
    //       ^ '(' needed. its a bug in gcc..
    // https://stackoverflow.com/questions/10509603/why-cant-i-initialize-a-reference-in-an-initializer-list-with-uniform-initializ
    ready{false}
// NOLINTNEXTLINE(whitespace/braces)
{
    // nothing to do right now..
}

MyInput::~MyInput() {
    end();
}


void MyInput::begin(Stream &out) {
    // clean up..
    end();
    // start up...
    if (ready == false) {
        // setup
        out.println("SettingsUI begin:");
        // sleepmode_init(out);
        out.println("  board_dotstar");
        board_dotstar.begin();
        board_dotstar.setPixelColor(0, board_dotstar_active_color);
        board_dotstar.show();
        als.begin(out);
        button_init(out);
        // out.println("  myencoder.begin");
        // myencoder.begin(funcISR);
        out.println("done.");
        ready = true;
        out.println("MyInput.begin ready = true");
    }
}

void MyInput::end() {
    if (ready) {
        // nothing to do..
    }
}

void MyInput::update() {
    if (ready) {
        // do it :-)
        light_update();
        // Serial.println("button.");
        mybutton.update();
        // Serial.println("update.");
        // delay(100);
    }
}




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// menu

void MyInput::menu__test_xxx(Print &out) {
    out.println(F("TODO"));
    out.println();
}

void MyInput::menu__set_yyy(Print &out, char *command) {
    out.println(F("Set yyy "));
    out.println(F("TODO"));

    out.print(F("Set yyy "));
    uint8_t command_offset = 1;
    uint8_t index = atoi(&command[command_offset]);
    // a better way than this would be to search for the ':'
    // i have used this a long time ago for MAC address format parsing
    // was something with 'tokenize' or similar..
    command_offset = 3;
    if (index > 9) {
        command_offset = command_offset +1;
    }
    out.print(index);
    out.print(F(" to "));
    uint16_t value = atoi(&command[command_offset]);
    out.print(value);
    // tlc.set_pixel_16bit_value(index, value, value, value);
    out.println();
}



// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ambientlight sensor

void MyInput::light_update() {
    als.update();
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// button

void MyInput::button_init(Stream &out) {
    out.println(F("setup button input:"));
    out.println(F("  set pinMode INPUT_PULLUP"));
    pinMode(mybutton.pin, INPUT_PULLUP);
    out.println(F("  mybutton.begin()"));
    mybutton.begin();
    out.println(F("  flag_filter_multi_click_events true"));
    mybutton.flag_filter_multi_click_events = true;
    out.println(F("  finished."));
}


boolean MyInput::mybutton_get_input(slight_ButtonInput *instance) {
    // read input + invert: button closes to GND.
    return !digitalRead((*instance).pin);
}

void MyInput::mybutton_event(slight_ButtonInput *instance) {
    // Serial.print(F("instance:"));
    // Serial.print((*instance).id);
    // Serial.print(F(" - event: "));
    // (*instance).printEventLast(Serial);
    // Serial.println();

    // react on event
    switch ((*instance).getEventLast()) {
        case slight_ButtonInput::event_down : {
            // Serial.println(F("down"));
        } break;
        case slight_ButtonInput::event_holddown : {
            Serial.print(F("duration active: "));
            Serial.println((*instance).getDurationActive());
        } break;
        case slight_ButtonInput::event_up : {
            // Serial.println(F("up"));
        } break;
        case slight_ButtonInput::event_click : {
            Serial.println(F("click"));
        } break;
        case slight_ButtonInput::event_click_long : {
            Serial.print(F("click long "));
            Serial.println((*instance).getDurationActive());
        } break;
        case slight_ButtonInput::event_click_double : {
            Serial.println(F("click double"));
        } break;
        case slight_ButtonInput::event_click_triple : {
            Serial.println(F("click triple"));
        } break;
        case slight_ButtonInput::event_click_multi : {
            Serial.print(F("click multi - count: "));
            Serial.println((*instance).getClickCount());
        } break;
    }  // end switch
}





// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THE END
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~