/******************************************************************************

    __doc__ = """
    animation.py - TLC5971 & FancyLED & 2D Array / Mapping.

    it combines the TLC5971 library with FancyLED and 2D Array / Mapping.

    Enjoy the colors :-)
    """

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


class MC_Animation {
public:

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // attributes

    // ##########################################
    // mappings
    // LEDBoard_4x4_16bit mapping

    static const uint16_t LEDBoard_col_count = 4;
    static const uint16_t LEDBoard_row_count = 4;
    static const uint16_t LEDBoard_pixel_count = (
        LEDBoard_row_count * LEDBoard_col_count);

    // Layouts for LEDBoard_4x4_HD
    // https://github.com/s-light/LEDBoard_4x4_HD

    // Horizontal
    // const uint8_t LEDBoard_single[LEDBoard_row_count][LEDBoard_col_count] = {
    //     {15, 14, 13, 12},
    //     {11, 10, 9, 8},
    //     {7, 6, 5, 4},
    //     {3, 2, 1, 0},
    // }

    // Vertical
    static constexpr uint8_t LEDBoard_single[LEDBoard_row_count][LEDBoard_col_count] = {
        {3, 7, 11, 15},
        {2, 6, 10, 14},
        {1, 5, 9, 13},
        {0, 4, 8, 12},
    };


    static const uint8_t Boards_col_count = 2;
    static const uint8_t Boards_row_count = 2;
    static const uint8_t Boards_count = Boards_col_count * Boards_row_count;
    static constexpr uint8_t Boards_positions[Boards_row_count][Boards_col_count] = {
        {2, 3},
        {1, 0},
        // ------
        // {1, 0},
        // {0},
    };

    static const uint8_t Matrix_col_count = LEDBoard_col_count * Boards_col_count;
    static const uint8_t Matrix_row_count = LEDBoard_row_count * Boards_row_count;
    static const uint8_t Matrix_pixel_count = Matrix_col_count * Matrix_row_count;

    static constexpr uint8_t LEDBoards_rotated[Matrix_row_count][Matrix_col_count] = {
        {15, 14, 13, 12,    3,  7, 11, 15},
        {11, 10,  9,  8,    2,  6, 10, 14},
        { 7,  6,  5,  4,    1,  5,  9, 13},
        { 3,  2,  1,  0,    0,  4,  8, 12},

        {12,  8,  4,  0,    0,  1,  2,  3},
        {13,  9,  5,  1,    4,  5,  6,  7},
        {14, 10,  6,  2,    8,  9, 10, 11},
        {15, 11,  7,  3,   12, 13, 14, 15},
    };


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // public types

    // enum function_command_pulse_count {
    //     _FC__WRTGS = 1,
    //     _FC__LATGS = 3,
    //     _FC__WRTFC = 5,
    //     _FC__LINERESET = 7,
    //     _FC__READFC = 11,
    //     _FC__TMGRST = 13,
    //     _FC__FCWRTEN = 15
    // };
    //
    // const uint8_t _FC_BIT_COUNT = CHIP_BUFFER_BIT_COUNT;
    //
    // struct function_control_t {
    //   const uint8_t offset;
    //   const uint8_t length;
    //   const uint16_t mask;
    //   const uint16_t defaultv;
    // };
    //
    // static constexpr function_control_t _FC_FIELDS_EMPTY = {
    //     .offset = 0,
    //     .length = 0,
    //     .mask = 0,
    //     .defaultv = 0,
    // };


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // constructor

    MC_Animation();
    ~MC_Animation();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // public functions
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // basic library api
    void begin();
    void update();
    void end();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // configurations

    uint8_t pmap[Matrix_row_count][Matrix_col_count];

private:

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // private functions
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    void pmap_init();

    uint8_t mymap_LEDBoard_4x4_HD(uint8_t col, uint8_t row);
    uint8_t mymap_LEDBoard_4x4_HD_CrystalLightGuide(uint8_t col, uint8_t row);

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // attributes
    bool ready;


};  // class MC_Animation

#endif  // MC_Animation_H_
