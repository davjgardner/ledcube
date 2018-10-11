#define NCOLS 9
#define NLAYERS 3
// addressed as two bytes: PORTB (8-13) in HOB and PORTD (0-7) in LOB
short l[] = {0x0200 /* 9*/, 0x0100 /* 8*/, 0x0080 /* 7*/, 0x0040 /* 6*/, 0x0020 /* 5*/,
             0x0010 /* 4*/, 0x0008 /* 3*/, 0x0004 /* 2*/, 0x0002 /* 1*/};
short g[] = {0x1000 /*12*/, 0x0800 /*11*/, 0x0400 /*10*/};

short prog[] = {l[0] | l[1] | l[2], l[0] | l[1] | l[2], l[0] | l[1] | l[2], 
                l[3] | l[4] | l[5], l[3] | l[4] | l[5], l[3] | l[4] | l[5], 
                l[6] | l[7] | l[8], l[6] | l[7] | l[8], l[6] | l[7] | l[8], };
int proglen = 3;

volatile int frame = 0;

// desired step rate 2Hz
// prescaler = 1024
// compare match = 7812 = (16*10^6) / (2 * 1024) - 1
#define CMP 7812
void setupTimer() {
  cli();
  
  TCCR1A = 0; // clear ctl regs
  TCCR1B = 0;
  TCNT1 = 0; // init counter

  OCR1A = CMP; // set compare match

  // turn on CTC mode (Clear Timer on Compare match
  TCCR1B |= (1 << WGM12);
  // set CS10 and CS12 bits for 1024 prescalar
  TCCR1B |= (1 << CS12) | (1 << CS10);
  // enable timer compare interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();
}

// step advance interrupt
ISR(TIMER1_COMPA_vect) {
  frame++;
  if (frame == proglen) frame = 0;
}

void setup() {
  cli();
  for (int i = 0; i < NCOLS; i++) {
    //pinMode(led_pins[i], OUTPUT);
    DDRB |= l[i] >> 8;
    DDRD |= l[i] & 0x00FF;
  }
  for (int i = 0; i < NLAYERS; i++) {
    //pinMode(gnd_pins[i], OUTPUT);
    DDRB |= g[i] >> 8;
    DDRD |= g[i] & 0x00FF;
  }
  
  setupTimer();
}

void doWrite(short val) {
  PORTB = val >> 8;
  PORTD = val;
}

int plane = 0;

void loop() {
  short val = g[plane];
  val |= prog[frame * NLAYERS + plane];
  doWrite(val);
  plane++;
  if (plane == NLAYERS) plane = 0;
}
