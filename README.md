# LED Cube

A code for a work-in-progress LED Cube.

### Cube Architecture

Each layer, or plane, of the cube connects all cathodes together. Anodes are connected in vertical columns. Each column can be turned on independently. To turn on a particular LED, its column is turned on and its layer is connected to ground.

To display a particular pattern for the whole cube, the layers are cycled. For each layer, the columns of the desired LEDs are brought high and their ground plane is brought low. A fast enough cycle fools the eye into thinking the layers are on at the same time.

So far, a 3x3x3 cube has been built. An 9x9x9 cube is in the works.

For a 3x3x3 cube, all controls (9 columns, 3 layers) could be mapped to individual pins on an Arduino (in this case, an Arduino Micro). For an 9x9x9 cube, data line multiplexing will be necessary.

Shift registers are used to achieve the needed 90 data lines.

The shift registers are connected as follows:

```
y

| 1  1  3  3  5  5  7  7 10
| 0  1  3  3  5  5  7  8  9
| 0  1  3  3  5  5  7  8  9
| 0  1  2  3  5  6  7  8  9
| 0  1  2  3  5  6  7  8  9
| 0  1  2  4  4  6  7  8  9
| 0  1  2  4  4  6  7  8  9
| 0  2  2  4  4  6  6  8  9
| 0  2  2  4  4  6  6  8  9
|__________________________ x

GND:
layer: 0  1  2  3  4  5  6  7  8
SR:   10 10 10 10 10 10 10 11 11

```

The ground layers are connected to shift registers 10 and 11.

This arrangement was chosen to maximize physical locality of columns while being easily addressable from software. The shift registers are connected snaking up and down the y-axis.

The following formula converts an LED address `(x, y)` to a shift register / offset pair (`SRk[off]`). We first flatten the two coordinates into a single string, then index into that string modulo 8. The conditional deals with the wrapping arrangement of the shift register connections.

```c
i = 9 * x + ((x % 2 == 0)? y : 8 - y);
k = i / 8;
off = i % 8;
```

It is actually more useful to address the LEDs offset-first, as that is the order they will be loaded onto the shift registers:

It would be possible to chain all of the shift registers together and only use one data pin on the microcontroller, but this would require 90 shift register clocks per frame. We can instead connect the data lines of each shift register to separate digital pins and load them in parallel. This means we can load a frame with just 8 shift register clocks. The data layout then looks as follows, again using `SRk[off]` notation:

```
B {0[0]  1[0]  2[0]  3[0]  4[0]  5[0]} C {6[0]  7[0]  8[0]  9[0] 10[0] 11[0]}
B {0[1]  1[1]  2[1]  3[1]  4[1]  5[1]} C {6[1]  7[1]  8[1]  9[1] 10[1] 11[1]}
...
```

The data inputs of shift registers 0-5 are connected to the ATMEGA's PORT B, and shift registers 6-11 are connected to PORT C.

### Test Programs

Tests so far are for a 3x3x3 cube which is fully built.

- `tests/cubetest1` is a basic test program which cycles through the LEDs with all data channels connected directly to the Arduino
- `tests/cubetest2` sets up a system for displaying a full cube state - strobing the layers and displaying an animation. It sets up a recurring timer interrupt to change animation frames. It attempts to use AVR PORT registers, but these were not mapped as expected on the Arduino Micro
- `tests/cubetest3` is a simple test for a cube controlled by shift registers
- `tests/cubetest4` implements the functionality of `cubetest2` on a shift register architecture and has some full programs
