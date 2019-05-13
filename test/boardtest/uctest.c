#include <avr/io.h>
#include <util/delay.h>

#define sbi(b, p) b |= (1 << p)
#define cbi(b, p) b &= ~(1 << p)
#define bit_set(b, p) b & (1 << p)

#define PRT PORTD
#define PIN PD7

#define DLY 100

int main(void) {
    sbi(DDRD, PIN);

    for(;;) {
        sbi(PRT, PIN);
        _delay_ms(DLY);
        cbi(PRT, PIN);
        _delay_ms(DLY);
    }
}
