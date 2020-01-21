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



#ifndef SRC_ARDUINO_MC_INPUT_H_
#define SRC_ARDUINO_MC_INPUT_H_


// include Core Arduino functionality
#include <Arduino.h>

#include <slight_DebugMenu.h>

#include <Adafruit_DotStar.h>

#include <slight_ButtonInput.h>

#include <slight_TSL2591AutoSensitivity.h>

#include "./animation.h"
#include "./mapping.h"


class MyInput {
 public:
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor

    MyInput(
        MyAnimation &animation
    );
    // MyInput(const slight_ButtonInput::tcbfOnEvent button_event);
    ~MyInput();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // basic library api
    void begin(Stream &out);
    void update();
    void end();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // CONST

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // attributes & objects

    // OnBoardDotstar
    Adafruit_DotStar board_dotstar = Adafruit_DotStar(1, 8, 6, DOTSTAR_BGR);

    // slight_ButtonInput mybutton;
    boolean mybutton_get_input(slight_ButtonInput *instance);
    void mybutton_event(slight_ButtonInput *instance);

    slight_ButtonInput mybutton = slight_ButtonInput(
        // uint8_t id_new
        1,
        // uint8_t pin_new,
        A4,
        // tCallbackFunctionGetInput callbackGetInput_new,
        std::bind(&MyInput::mybutton_get_input, this, std::placeholders::_1),
        // tCallbackFunction callbackOnEvent_new,
        std::bind(&MyInput::mybutton_event, this, std::placeholders::_1),
        // const uint16_t duration_debounce_new = 20,
        10,
        // const uint16_t duration_holddown_new = 1000,
        1000,
        // const uint16_t duration_click_long_new =   3000,
        2000,
        // const uint16_t duration_click_double_new = 250
        250
    );

    // Ambient Light Sensor
    slight_TSL2591AutoSensitivity als = slight_TSL2591AutoSensitivity();
    void als_debugout(Print &out);
    bool als_debugout_enabled = false;
    double get_als_brightness_automatic(void);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // public functions

    // menu & helper
    void menu__test_xxx(Print &out);
    void menu__set_yyy(Print &out, char *command);


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // configurations

    bool ambientlight_run = true;
    bool als_sets_brightness = false;

    uint16_t filter_duration = 20 * 1000;  // ms
    float light_event_threshold = 0.1;

    // map ambient lux to animation.brightness
    static const size_t light_map_count = 7;
    MultiMap<double, light_map_count> light_map{
        // als lux
        std::array<double, light_map_count>{
            0.0001,
            0.0100,
            0.1000,
            1.5000,
            10.000,
            200.00,
            10000.0,
        },
        // animation.brightness
        std::array<double, light_map_count>{
            0.00005,
            0.0050,
            0.0500,
            0.1000,
            0.2000,
            0.5000,
            0.8000,
        }
    };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // helper

 private:
    MyAnimation &animation;

    // ambientlight sensor
    uint32_t als_debugout_timeStamp = 0;
    void als_setup(Print &out);
    void als_update(Print &out);
    void als_handle_sens_conf_change(Print &out);
    void als_handle_lux_change(Print &out);
    void als_debugout_sens_conf_change(Print &out);
    double als_brightness_automatic = 0.0001;

    // // button input
    void button_init(Stream &out);

    // helper
    void print_runtime(Print &out);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // internal attributes
    bool ready;

    uint32_t light_start = 0;
    uint32_t light_end = 0;
    uint32_t light_loopcount = 0;
    float effect_position = 0.0;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // power modes
    uint32_t board_dotstar_standby_color = Adafruit_DotStar::Color(0, 0, 10);
    uint32_t board_dotstar_wait_color = Adafruit_DotStar::Color(100, 100, 0);
    uint32_t board_dotstar_active_color = Adafruit_DotStar::Color(0, 40, 0);

};  // class MyInput

#endif  // SRC_ARDUINO_MC_INPUT_H_
