#ifndef CUBE_DISPLAY_HH
#define CUBE_DISPLAY_HH

#include <cstdlib>
#include <cstdint>

#include "cube_defs.h"

class CubeState {
private:
    // TODO: some state representation here:
    short **state;

public:
    // Sets all lights to off
    void zero() {
        // TODO
    }

    /* The following functions, when called with out-of-bounds coordinates,
         will do nothing. */
    void turn_on(int x, int y, int z) {
        // TODO
    }

    void turn_off(int x, int y, int z) {
        // TODO
    }

    void toggle(int x, int y, int z) {
        // TODO
    }

    // Returns false if arguments out of bounds.
    bool is_on(int x, int y, int z) {
        // TODO
        return false;
    }
};

class CubeDisplay {

public:

    // Advance state by `dt` milliseconds
    virtual void update(int dt);

    // Fetch the current state of the cube for display
    virtual CubeState *get_frame();
};


/**
 * Snake which moves randomly around the cube. Configurable length and speed.
 * Currently cube-shape only.
 *
 * Potential augments:
 * - wrapping
 */
class RandomSnakeDisplay : CubeDisplay {

#define MAX_LEN 10

private:
    uint8_t len;

    // circular snake buffer
    /* has to be MAX_LEN + 1 so that we can still access
         old tail after adding new head even for a MAX_LEN snake */
    uint8_t snake[MAX_LEN + 1][3];
    unsigned char head = 0; // TODO: uint8_t

    // speed in milliseconds per step
    uint32_t speed;
    uint32_t t;

    CubeState state;

public:
    RandomSnakeDisplay(uint8_t len, uint32_t speed): len{len}, speed{speed} {
        srand(20190104);

        snake[0][0] = rand() % CX;
        snake[0][1] = rand() % CY;
        snake[0][2] = rand() % CZ;
        for (uint8_t i = 0; i < len; ++i) {
            snake[i][0] = snake[0][0];
            snake[i][1] = snake[0][1];
            snake[i][2] = snake[0][2];
        }
    }

    void update(int dt) {
        t += dt;
        while (t > speed) {
            t -= speed;
            head = (head + 1) % len;

            int8_t delta = (rand() % 2) ? 1 : -1;
            int8_t axis = rand() % 3;
            snake[head][axis] += delta;

            // bounds check
            // TODO: wrapping
            if (snake[head][axis] < 0) snake[head][axis] = 0;
            else if (snake[head][axis] >= CSIZE) snake[head][axis] = CSIZE - 1;

            // update state
            state.turn_on(snake[head][0], snake[head][1], snake[head][2]);
            // this would be (head - len + 1), but we want to turn off old tail
            uint8_t tail = (head - len) % len;
            state.turn_off(snake[tail][0], snake[tail][1], snake[tail][2]);
        }
    }

    CubeState *get_frame() {
        /* TODO:
         * - keep global state in giant array
         * - keep head and tail for circular buffer
         * - on update turn on [head] in global state, turn off [tail]
         *
         * then this function just returns pointer to global state
         */
        return &state;
    }
};

/**
 * Random field of lights. A light turns on or off every `speed` milliseconds
 */
class RandomFieldDisplay : CubeDisplay {
private:
    // milliseconds per update
    uint32_t speed;
    uint32_t t;

    CubeState state;

public:

    /**
     * `speed` is the number of milliseconds per light toggle
     * `init_prop` [0, 100) is the percentage of lights which are initially on
     */
    RandomFieldDisplay(uint32_t speed, uint32_t init_prop) : speed{speed} {
        srand(20180105);
        for (int x = 0; x < CX; ++x) {
            for (int y = 0; y < CY; ++y) {
                for (int z = 0; z < CZ; ++z) {
                    if (rand() % 100 < init_prop) {
                        state.turn_on(x, y, z);
                    }
                }
            }
        }
    }

    void update(int dt) {
        t += dt;
        while (t >= speed) {
            t -= speed;
            uint8_t x = rand() % CX;
            uint8_t y = rand() % CY;
            uint8_t z = rand() % CZ;
            state.toggle(x, y, z);
        }
    }

    CubeState *get_frame() {
        return &state;
    }
};

class RainDisplay : CubeDisplay {
private:
    uint32_t iv; // initial inverse velocity of drops (in ticks per light)
    int g; // gravity (acceleration of rain) TODO
    uint8_t tail; // rain streak length
    uint32_t tick; // how often to update (milliseconds)
    uint8_t density; // (0, 100) likelyhood of new drop each tick

    int8_t dpos[CSIZE][CSIZE];

    CubeState state;
    uint32_t t;
    uint32_t tick_count = 0;

public:
    RainDisplay(uint32_t init_iv, int g, uint8_t density)
        : iv{init_iv}, g{g}, density{density} {
        srand(20180105);
        state.zero();
        for (uint8_t x = 0; x < CSIZE; ++x) {
            for (uint8_t y = 0; y < CSIZE; ++y) {
                dpos[x][y] = -1;
            }
        }
    }

    void update(int dt) {
        t += dt;
        while (t >= tick) {
            t -= tick;
            tick_count++;

            while (tick_count >= iv) {
                // update drops
                for (uint8_t x = 0; x < CSIZE; ++x) {
                    for (uint8_t y = 0; y < CSIZE; ++y) {
                        if (dpos[x][y] >= 0) {
                            // turn off old top, turn on new bottom
                            state.turn_off(x, y, dpos[x][y]);
                            state.turn_on(x, y, dpos[x][y] - tail);

                            dpos[x][y]--;
                        }
                    }
                }
            }
            // maybe create new drop
            if (rand() % 100 < density) {
                uint8_t x, y;
                // find an empty column
                do {
                    x = rand() % CSIZE;
                    y = rand() % CSIZE;
                } while (dpos[x][y] != -1);
                // position is represented by the top of the drop
                dpos[x][y] = CSIZE - 1 + tail - 1;
                state.turn_on(x, y, CSIZE - 1);
            }
        }
    }

    CubeState *get_frame() {
        return &state;
    }
};

#endif
