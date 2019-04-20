/******************************************************************************

    __doc__ = """
    animation.py - TLC5971 & FancyLED & 2D Array / Mapping.

    it combines the TLC5971 library with FancyLED and 2D Array / Mapping.

    Enjoy the colors :-)
    """

    libraries used:
        ~ slight_DebugMenu
        ~ slight_TLC5957
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



#ifndef MC_Animation_H_
#define MC_Animation_H_

// include Core Arduino functionality
#include <Arduino.h>

#include <slight_DebugMenu.h>

#include <SPI.h>
#include <slight_TLC5957.h>




class MC_Animation {
public:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // structs

    // typedef void (* tAnimationUpdatePixel) ();
    // typedef void (* tAnimationUpdatePosition) ();
    //
    // struct animation_t {
    //   const tAnimationUpdatePixel update_pixel;
    //   const tAnimationUpdatePosition update_position;
    //   const uint16_t mask;
    //   const uint16_t defaultv;
    // };

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // attributes

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // pixel map
    // LEDBoard_4x4_16bit mapping

    static const uint16_t LEDBOARD_COL_COUNT = 4;
    static const uint16_t LEDBOARD_ROW_COUNT = 4;
    static const uint16_t LEDBOARD_PIXEL_COUNT = (
        LEDBOARD_ROW_COUNT * LEDBOARD_COL_COUNT);

    // Layouts for LEDBoard_4x4_HD
    // https://github.com/s-light/LEDBoard_4x4_HD

    static const uint8_t LEDBOARD_SINGLE
        [LEDBOARD_ROW_COUNT][LEDBOARD_COL_COUNT];


    static const uint8_t BOARDS_COL_COUNT = 2;
    static const uint8_t BOARDS_ROW_COUNT = 2;
    static const uint8_t BOARDS_COUNT = BOARDS_COL_COUNT * BOARDS_ROW_COUNT;
    static const uint8_t BOARDS_POSITIONS
        [BOARDS_ROW_COUNT][BOARDS_COL_COUNT];

    static const uint8_t MATRIX_COL_COUNT = LEDBOARD_COL_COUNT * BOARDS_COL_COUNT;
    static const uint8_t MATRIX_ROW_COUNT = LEDBOARD_ROW_COUNT * BOARDS_ROW_COUNT;
    static const uint8_t MATRIX_PIXEL_COUNT = MATRIX_COL_COUNT * MATRIX_ROW_COUNT;

    static const uint8_t LEDBOARDS_ROTATED
        [MATRIX_ROW_COUNT][MATRIX_COL_COUNT];

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // TLC5957

    // possible options and defaults:
    // slight_TLC5957(
    //     uint8_t chip_count,
    //     uint8_t lat_pin = 7,
    //     uint8_t gclk_pin = 9,
    //     uint8_t sclk_pin = SCK,
    //     uint8_t sout_pin = MOSI,
    //     uint8_t sin_pin = MISO
    // );
    // use default pins
    slight_TLC5957 tlc = slight_TLC5957(MATRIX_PIXEL_COUNT);


    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor

    MC_Animation();
    ~MC_Animation();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // public functions

    // basic library api
    void begin(Stream &out);
    void update();
    void end();

    // menu & helper
    void menu__set_pixel(Print &out, char *command);
    void menu__test_buffer(Print &out);
    void print_tlc_buffer(Print &out);

    float gsclock_set_frequency_MHz(float frequency_MHz);
    float gsclock_get_frequency_MHz();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // helper

    float map_range(
        float x, float in_min, float in_max, float out_min, float out_max);
    float map_range(
        int x, int in_min, int in_max, float out_min, float out_max);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // configurations

    uint8_t pmap[MATRIX_ROW_COUNT][MATRIX_COL_COUNT];

    bool animation_run = true;

    //uint16_t animation_interval = 1000; //ms
    uint16_t animation_interval = 100; //ms

    uint8_t step = 0;

    float contrast = 0.99;
    float brightness = 0.1;
    float stepsize = 0.1;

    // const float PI = 3.141592;
    // is already defined...

private:

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // private functions

    // animation
    void animation_init(Stream &out);
    void animation_update();


    // const uint8_t step_wrap = MATRIX_COL_COUNT;
    const uint8_t step_wrap = MATRIX_PIXEL_COUNT;
    void effect__step_inc();
    void effect__pixel_checker();
    void effect__line();

    float _offset = 0;
    void effect__offset_inc();
    void effect__test();
    void effect__plasma();

    // others
    void pmap_init();

    uint8_t mymap_LEDBoard_4x4_HD(uint8_t col, uint8_t row);
    uint8_t mymap_LEDBoard_4x4_HD_CrystalLightGuide(uint8_t col, uint8_t row);

    void tlc_init(Stream &out);

    void gsclock_init(Print &out);
    void setup_D9_10MHz();
    void set_D9_period_reg(uint8_t period_reg);
    uint8_t get_D9_period_reg();

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // attributes
    bool ready;
    unsigned long animation_timestamp = 0;

};  // class MC_Animation

#endif  // MC_Animation_H_
