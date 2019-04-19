# magic_crystal_animation
animation firmware for [magic_crystal](https://github.com/s-light/magic_crystal)

there are two versions:
- CircuitPython [src/](src/)
- Arduino [src_arduino/](src_arduino/)

currently the CP version is working fine but slow.
therefore the port to C++.

if the porting is finished i try and keep theme functional similar.


## animation

sparkling effect with some options:
- base color
- sparkling brightness
- total brightness

## hardware

Controller: Adafruit ItsyBitsy M4

[LEDBoard_4x4_HD](https://github.com/s-light/LEDBoard_4x4_HD)  
with controller TLC5957

ambient light sensor: ?
remote control: ?
