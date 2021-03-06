<!--lint disable list-item-indent-->
<!--lint disable list-item-bullet-indent-->

# magic_crystal_animation
animation firmware for [magic_crystal](https://github.com/s-light/magic_crystal)

visit: [project page](https://s-light.github.io/magic_crystal_animation/)

there are two versions:
- CircuitPython [src/](src/)
- Arduino [src_arduino/](src_arduino/)

the CP version is working fine but slow.  
that is the reason i ported this to Arduino / C++ -
this is really fast / smooth (~120fps) :-)  

for the arduino sketch you need a special version of the
[TSL2591 library](https://github.com/s-light/Adafruit_TSL2591_Library/tree/auto_sensitivity).
(hopefully this gets merged at some point ;-) )

you can find a video at [this blog post](http://blog.s-light.eu/my-magic-crystal-is-alive/)
<video
    src="http://s-light.eu/video/VID_20190422_190246.webm"
    style="max-width:100%; max-height:100vh;"
    controls=""
    loop="">
</video>



## animation

'plasma' effect  
options:
- duration
- base hue
- contrast
- brightness

the animation brightness is controlled by the TSL2591 ambient light sensor.
the mapping between incoming lux values and brightness [is hardcoded](src_arduino/myinput.h#L142)

## hardware

Controller: Adafruit ItsyBitsy M4

[LEDBoard_4x4_HD](https://github.com/s-light/LEDBoard_4x4_HD)  
with controller TLC5957

ambient-light sensor: [TSL2591](https://github.com/adafruit/Adafruit_TSL2591_Library)
