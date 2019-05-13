/* shiftregtest.c
 *
 * Basic functionality test for shift registers.
 */

#include <avr/io.h>
#include <util/delay.h>

#define sbi(b, p) (b) |= (1 << (p))
#define cbi(b, p) (b) &= ~(1 << (p))
#define bit_set(b, p) (b) & (1 << (p))

#define SR 1
#define CLK_PRT PORTD
#define CLK_PIN PD6
#define LCH_PRT PORTD
#define LCH_PIN PD7

#define DELAY 250

void digital_write(int pin, unsigned char state) {
    if (pin < 6) {
        sbi(DDRB, pin);
        if (state) {
            sbi(PORTB, pin);
        } else {
            cbi(PORTB, pin);
        }
    } else {
        sbi(DDRC, pin - 6);
        if (state) {
            sbi(PORTC, pin - 6);
        } else {
            cbi(PORTC, pin - 6);
        }
    }
}

#define LSB_FIRST 0
#define MSB_FIRST 1

// write `data` to pin `sr` LSB-first
void shift_out(int sr, unsigned char data, unsigned char mode) {
    if (mode == LSB_FIRST) {
        for (int i = 0; i < 8; i++) {
            digital_write(sr, (data >> i) & 0x1);
            sbi(CLK_PRT, CLK_PIN);
            cbi(CLK_PRT, CLK_PIN);
        }
    } else {
        for (int i = 7; i >= 0; i--) {
            digital_write(sr, (data >> i) & 0x1);
            sbi(CLK_PRT, CLK_PIN);
            cbi(CLK_PRT, CLK_PIN);
        }
    }
    sbi(LCH_PRT, LCH_PIN);
    cbi(LCH_PRT, LCH_PIN);
}

// basic uc test
void test1(void) {
    sbi(DDRB, PB0);
    for (;;) {
        digital_write(0, 1);
        _delay_ms(250);
        digital_write(0, 0);
        _delay_ms(250);
    }
}

// cycle through outputs
void test2(void) {
    sbi(DDRB, SR);
    sbi(DDRD, CLK_PIN);
    sbi(DDRD, LCH_PIN);
    for (int i = 0; ; i++) {
        if (i % 8 == 0) {
            sbi(PORTB, SR);
        }

        sbi(CLK_PRT, CLK_PIN);
        cbi(CLK_PRT, CLK_PIN);

        sbi(LCH_PRT, LCH_PIN);
        cbi(LCH_PRT, LCH_PIN);

        _delay_ms(DELAY);

        if (i % 8 == 0) {
            cbi(PORTB, SR);
            i = 0;
        }
    }
}

// test shift_out function (cycle through)
void test3(void) {
    for (;;) {
        for (int i = 0; i < 8; i++) {
            shift_out(SR, 1 << i, LSB_FIRST);
            _delay_ms(DELAY);
        }
    }
}

// test patterns
void test4(void) {
    for (;;) {
        shift_out(SR, 0b10101010, LSB_FIRST);
        _delay_ms(DELAY);
        shift_out(SR, 0b01010101, LSB_FIRST);
        _delay_ms(DELAY);
    }
}

// test the two shift registers controlling ground connections
void test_gnd(void) {
    for (;;) {
        for (int i = 0; i < 8; i++) {
            shift_out(10, 1 << i, LSB_FIRST);
            _delay_ms(DELAY);
        }
        shift_out(10, 0, LSB_FIRST);
        for (int i = 0; i < 8; i++) {
            shift_out(11, 1 << i, LSB_FIRST);
            _delay_ms(DELAY);
        }
        shift_out(11, 0, LSB_FIRST);
    }
}

int main(void) {
    sbi(DDRB, SR);
    sbi(DDRD, CLK_PIN);
    sbi(DDRD, LCH_PIN);
    test3();
}
