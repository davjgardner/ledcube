# LED Cube

A code for a work-in-progress LED Cube.

### Cube Architecture

Each layer, or plane, of the cube connects all cathodes together. Anodes are connected in vertical columns. Each column can be turned on independently. To turn on a particular LED, its column is turned on and its layer is connected to ground.

To display a particular pattern for the whole cube, the layers are cycled. For each layer, the columns of the desired LEDs are brought high and their ground plane is brought low. A fast enough cycle fools the eye into thinking the layers are on at the same time.

So far, a 3x3x3 cube has been built. An 8x8x8 cube is planned.

For a 3x3x3 cube, all controls (9 columns, 3 layers) could be mapped to individual pins on an Arduino (in this case, an Arduino Micro). For an 8x8x8 cube, data line multiplexing will be necessary.

Shift registers will be used to achieve the needed 72 data lines.

### Test Programs

Tests so far are for a 3x3x3 cube which is fully built.

- `cubetest1` is a basic test program which cycles through the LEDs with all data channels connected directly to the Arduino
- `cubetest2` sets up a system for displaying a full cube state - strobing the layers and displaying an animation. It sets up a recurring timer interrupt to change animation frames. It attempts to use AVR PORT registers, but these were not mapped as expected on the Arduino Micro
- `cubetest3` is a simple test for a cube controlled by shift registers
- `cubetest4` implements the functionality of `cubetest2` on a shift register architecture and has some full programs
