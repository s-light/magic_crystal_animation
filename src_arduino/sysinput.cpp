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


// include own headerfile
#include "./sysinput.h"

// include Core Arduino functionality
#include <Arduino.h>

#include <slight_DebugMenu.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_TSL2591.h"

#include <slight_ButtonInput.h>


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// functions

MC_Input::MC_Input() {
    ready = false;
}

MC_Input::~MC_Input() {
    end();
}

void MC_Input::begin(Stream &out) {
    // clean up..
    end();
    // start up...
    if (ready == false) {
        // setup
        light_init(out);

        // enable
        ready = true;
    }
}

void MC_Input::end() {
    if (ready) {
        // nothing to do..
    }
}

void MC_Input::update() {
    if (ready) {
        // do it :-)
        light_update();
    }
}




// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// menu

void MC_Input::menu__test_xxx(Print &out) {
    out.println(F("TODO"));
    out.println();
}

void MC_Input::menu__set_yyy(Print &out, char *command) {
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

void MC_Input::light_init(Stream &out) {
    out.println(F("setup ambientlight sensor:"));
    out.println(F("TODO"));
    // TODO(s-light): implement

    // out.println(F("  tlc.begin()"));
    // tlc.begin();

    // out.print(F("  tlc.get_fc_ESPWM(): "));
    // out.print(tlc.get_fc_ESPWM());
    // out.println();
    out.println(F("  finished."));
}

void MC_Input::light_update() {
    // TODO(s-light): implement
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// button

void MC_Input::button_init(Stream &out) {
    out.println(F("setup button input:"));
    out.println(F("TODO"));

    // out.println(F("  tlc.begin()"));
    // mybutton.begin();

    // out.print(F("  tlc.get_fc_ESPWM(): "));
    // out.print(tlc.get_fc_ESPWM());
    // out.println();
    out.println(F("  finished."));
}

bool MC_Input::button_getinput(byte id, byte pin) {
    // read input invert reading - button closes to GND.
    return !digitalRead(pin);
}

// void MC_Input::button_event(slight_ButtonInput *instance, byte event) {
//     // Serial.print(F("Instance ID:"));
//     // Serial.println((*instance).getID());
//
//     Serial.print(F("Event: "));
//     (*instance).printEvent(Serial, event);
//     Serial.println();
//
//     // show event additional infos:
//     switch (event) {
//         // case slight_ButtonInput::event_StateChanged : {
//         //     Serial.print(F("\t state: "));
//         //     (*instance).printState(Serial);
//         //     Serial.println();
//         // } break;
//         // click
//         // case slight_ButtonInput::event_Down : {
//         //     Serial.print(F("the button is pressed down! do something.."));
//         // } break;
//         case slight_ButtonInput::event_HoldingDown : {
//             Serial.print(F("duration active: "));
//             Serial.println((*instance).getDurationActive());
//         } break;
//         // case slight_ButtonInput::event_Up : {
//         //     Serial.print(F("up"));
//         // } break;
//         case slight_ButtonInput::event_Click : {
//             Serial.print(F("click"));
//         } break;
//         // case slight_ButtonInput::event_ClickLong : {
//         //     Serial.print(F("click long"));
//         // } break;
//         case slight_ButtonInput::event_ClickDouble : {
//             Serial.print(F("click double"));
//         } break;
//         // case slight_ButtonInput::event_ClickTriple : {
//         //     Serial.print(F("click triple"));
//         // } break;
//         case slight_ButtonInput::event_ClickMulti : {
//             Serial.print(F("click count: "));
//             Serial.println((*instance).getClickCount());
//         } break;
//     }  // end switch
// }






// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// THE END
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
