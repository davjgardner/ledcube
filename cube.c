/* cube.h
 *
 * 9x9x9 LED Cube runtime
 *
 * David Gardner 2018
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define sbi(b, p) b |= (1 << p)
#define cbi(b, p) b &= ~(1 << p)
#define bit_set(b, p) b & (1 << p)

// processor frequency
#define FRQ 16_000_000

// step change rate in Hz
#define FRAMERATE 5
// compare match value
#define CMP FRQ / (FRAMERATE * 1024) - 1;

// shift register clock (on PORTD)
#define PIN_CLK PD7
// shift register latch (RCLK) (on PORTD)
#define PIN_LATCH PD6

void setup_timers() {
    cli();
    // clear registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

    // set compare match value
    OCR1A = CMP;

    // turn on CTC mode
    sbi(TCCR1B, WGM12);
    // prescalar = 1024
    sbi(TCCR1B, CS12);
    sbi(TCCR1B, CS10);
    // enable interrupt
    sbi(TIMSK1, OCIE1A);

    sei();
}

/**
 * Timer 1 ISR (called at FRAMERATE)
 */
ISR(TIMER1_COMPA_vect) {
    // setup / advance to next frame
}

/**
 * Write a frame to the cube.
 * The frame is arranged as an array of 8 shorts, each of which contains the
 * values for PORTB (SR 0-5) in the least significant byte, and PORTC (SR 6-12)
 * in the most significant byte.
 */
void writeframe(short* data) {
    for (int i = 0; i < 8; i++) {
        PORTB = *(data + i);
        PORTC = *(data + i) >> 8;
        sbi(PORTD, PIN_CLK);
        // TODO: delay?
        cbi(PORTD, PIN_CLK);
    }
    sbi(PORTD, PIN_LATCH);
    // TODO: delay?
    cbi(PORTD, PIN_LATCH);
}

int main(void) {
    setup_timers();

    // tight loop through layers
    for (;;) {

    }
}
