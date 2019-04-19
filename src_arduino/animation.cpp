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


// include Core Arduino functionality
#include <Arduino.h>

// include SPI library
#include <SPI.h>

// include own headerfile
#include "animation.h"

// namespace MCAnim = MC_Animation;

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// functions
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


MC_Animation::MC_Animation() {
    ready = false;
}

MC_Animation::~MC_Animation() {
    end();
}

void MC_Animation::begin() {
    // clean up..
    end();
    // start up...
    if (ready == false) {
        // setup
        // TODO(s-light)
    }
}

void MC_Animation::end() {
    if (ready) {
        // nothing to do..
    }
}

void MC_Animation::update() {
    if (ready) {
        // do something :-)
    }
}





uint8_t MC_Animation::mymap_LEDBoard_4x4_HD(
    uint8_t col, uint8_t row
) {
    // """Map row and col to pixel_index."""
    // get Board position
    uint8_t board_col = col / LEDBoard_col_count;
    uint8_t board_row = row / LEDBoard_row_count;
    uint8_t board_sub_col = col % LEDBoard_col_count;
    uint8_t board_sub_row = row % LEDBoard_row_count;

    uint8_t board_offset = Boards_positions[board_row][board_col];
    uint8_t pixel_offset = LEDBoard_single[board_sub_row][board_sub_col];

    uint8_t pixel_index = (pixel_offset * Boards_count) + board_offset;

    return pixel_index;
}


uint8_t MC_Animation::mymap_LEDBoard_4x4_HD_CrystalLightGuide(
    uint8_t col, uint8_t row
) {
    // """Map row and col to pixel_index."""
    // get Board position
    uint8_t board_col = col / LEDBoard_col_count;
    uint8_t board_row = row / LEDBoard_row_count;
    // uint8_t board_sub_col = col % LEDBoard_col_count;
    // uint8_t board_sub_row = row % LEDBoard_row_count;

    uint8_t board_offset = Boards_positions[board_row][board_col];
    // pixel_offset = LEDBoard_single[board_sub_row][board_sub_col];

    uint8_t pixel_offset = LEDBoards_rotated[row][col];
    // print("{:>3} {:>3}: {:>3}".format(col, row, pixel_offset));
    uint8_t pixel_index = (pixel_offset * Boards_count) + board_offset;

    return pixel_index;
}

// pmap = PixelMap2D(
//     row_count=Matrix_row_count,
//     col_count=Matrix_col_count,
//     // map_function=mymap_LEDBoard_4x4_HD
//     map_function=mymap_LEDBoard_4x4_HD_CrystalLightGuide
// )


// ##########################################
// THE END
// ##########################################
