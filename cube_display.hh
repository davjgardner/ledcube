#ifndef CUBE_DISPLAY_HH
#define CUBE_DISPLAY_HH

#include <cstdlib>

#include "cube_defs.h"

struct CubeState {
    // TODO: some state representation here:
    short **state;

    void turn_on(int x, int y, int z) {
        // TODO
    }

    void turn_off(int x, int y, int z) {
        // TODO
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
    int len;

    // circular snake buffer
    /* has to be MAX_LEN + 1 so that we can still access
         old tail after adding new head even for a MAX_LEN snake */
    int snake[MAX_LEN + 1][3];
    unsigned char head = 0; // TODO: uint8_t

    // speed in milliseconds per step
    int speed;
    int t;

    CubeState state;

public:
    RandomSnakeDisplay(int len, int speed): len{len}, speed{speed} {
        srand(20190104);

        snake[0][0] = rand() % CX;
        snake[0][1] = rand() % CY;
        snake[0][2] = rand() % CZ;
        for (int i = 0; i < len; ++i) {
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

            int delta = (rand() % 2) ? 1 : -1;
            int axis = rand() % 3;
            snake[head][axis] += delta;

            // bounds check
            // TODO: wrapping
            if (snake[head][axis] < 0) snake[head][axis] = 0;
            else if (snake[head][axis] >= CSIZE) snake[head][axis] = CSIZE - 1;

            // update state
            state.turn_on(snake[head][0], snake[head][1], snake[head][2]);
            // this would be (head - len + 1), but we want to turn off old tail
            unsigned char tail = (head - len) % len;
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

#endif
