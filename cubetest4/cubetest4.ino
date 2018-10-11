#define NCOLS 9
#define NLAYERS 3

#define CLK 2
#define DATA 3
#define LATCH 4
#define OE 5

// shift out two bytes
short l[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100};
short g[] = {6, 7, 8};

// pinwheel
short wheel[] = {4,
                 0, l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], 0,
                 l[6] | l[7] | l[8], l[3] | l[4] | l[5], l[0] | l[1] | l[2],
                 l[3] | l[4] | l[5], l[3] | l[4] | l[5], l[3] | l[4] | l[5], 
                 l[0] | l[1] | l[2], l[3] | l[4] | l[5], l[6] | l[7] | l[8],};

// size-1 snake
short snake1[] = {17, 
                  l[0], 0, 0,
                  l[1], 0, 0,
                  l[2], 0, 0,
                  0, l[2], 0,
                  0, 0, l[2],
                  0, 0, l[5],
                  0, 0, l[8],
                  0, l[8], 0,
                  l[8], 0, 0,
                  l[7], 0, 0,
                  l[6], 0, 0,
                  0, l[6], 0,
                  0, 0, l[6],
                  0, 0, l[3],
                  0, 0, l[0],
                  0, l[0], 0,};

// size-2 snake
short snake2[] = {16,
                  l[0], 0, 0,
                  l[0] | l[1], 0, 0,
                  l[1] | l[2], 0, 0,
                  l[2], l[2], 0,
                  0, l[2], l[2],
                  0, 0, l[2] | l[5],
                  0, 0, l[5] | l[8],
                  0, l[8], l[8],
                  l[8], l[8], 0,
                  l[7] | l[8], 0, 0,
                  l[6] | l[7], 0, 0,
                  l[6], l[6], 0,
                  0, l[6], l[6],
                  0, 0, l[3] | l[6],
                  0, 0, l[0] | l[3],
                  0, l[0], l[0],
                  l[0], l[0], 0};

// boom
short boom[] = {3, 
                0, l[4], 0,
                l[4], l[1] | l[3] | l[5] | l[7], l[4],
                l[0] | l[2] | l[6] | l[8], 0, l[0] | l[2] | l[6] | l[8],};

short cubebounce[] = {30,
                    l[0], 0, 0,
                    l[0] | l[1] | l[3] | l[4], l[0] | l[1] | l[3] | l[4], 0,
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    0, l[4] | l[5] | l[7] | l[8],l[4] | l[5] | l[7] | l[8],
                    0, 0, l[8],
                    0, l[4] | l[5] | l[7] | l[8],l[4] | l[5] | l[7] | l[8],
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    l[1] | l[2] | l[4] | l[5], l[1] | l[2] | l[4] | l[5], 0,
                    l[2], 0, 0,
                    l[1] | l[2] | l[4] | l[5], l[1] | l[2] | l[4] | l[5], 0,
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    0, l[3] | l[4] | l[6] | l[7], l[3] | l[4] | l[6] | l[7], 
                    0, 0, l[6],
                    0, l[3] | l[4] | l[6] | l[7], l[3] | l[4] | l[6] | l[7],
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    l[4] | l[5] | l[7] | l[8], l[4] | l[5] | l[7] | l[8], 0,
                    l[8], 0, 0,
                    l[4] | l[5] | l[7] | l[8], l[4] | l[5] | l[7] | l[8], 0,
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    0, l[0] | l[1] | l[3] | l[4], l[0] | l[1] | l[3] | l[4],
                    0, 0, l[0],
                    0, l[0] | l[1] | l[3] | l[4], l[0] | l[1] | l[3] | l[4],
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    l[3] | l[4] | l[6] | l[7], l[3] | l[4] | l[6] | l[7], 0,
                    l[6], 0, 0,
                    l[3] | l[4] | l[6] | l[7], l[3] | l[4] | l[6] | l[7], 0,
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    0, l[1] | l[2] | l[4] | l[5], l[1] | l[2] | l[4] | l[5],
                    l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8],
                    l[0] | l[1] | l[3] | l[4], l[0] | l[1] | l[3] | l[4], 0,
};

short swirl[] = {8,
                 l[0] | l[1] | l[3], 0, l[5] | l[7] | l[8],
                 l[0] | l[1] | l[2], 0, l[2] | l[5] | l[8],
                 l[1] | l[2] | l[5], 0, l[1] | l[2] | l[5],
                 l[2] | l[5] | l[8], 0, l[0] | l[1] | l[2],
                 l[5] | l[7] | l[8], 0, l[0] | l[1] | l[3],
                 l[6] | l[7] | l[8], 0, l[0] | l[3] | l[6],
                 l[3] | l[6] | l[7], 0, l[3] | l[6] | l[7], 
                 l[0] | l[3] | l[6], 0, l[6] | l[7] | l[8],
};

short* progs[] {swirl, snake2, wheel, cubebounce};
int nprogs = 4;
int prognum = 0;

//short prog[] = {l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], 0, 0,
//                0, l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8], 0,
//                0, 0, l[0] | l[1] | l[2] | l[3] | l[4] | l[5] | l[6] | l[7] | l[8]};

//short prog[] = {l[5], 0, 0, 0, l[5], 0, 0, 0, l[5]};
//short prog[] = {l[5], l[5], l[5], l[5], l[5], l[5], l[5], l[5], l[5], };

//short prog[] = {l[0] | l[1] | l[2], l[0] | l[1] | l[2], l[0] | l[1] | l[2], 
//                l[3] | l[4] | l[5], l[3] | l[4] | l[5], l[3] | l[4] | l[5], 
//                l[6] | l[7] | l[8], l[6] | l[7] | l[8], l[6] | l[7] | l[8], };

short* prog = swirl;

int proglen = 17;

volatile int frame = 0;

// desired step rate 2Hz
// prescaler = 1024
// compare match = 7812 = (16*10^6) / (2 * 1024) - 1
#define CMP 3000
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

// step advance ISR
ISR(TIMER1_COMPA_vect) {
  frame++;
  if (frame == prog[0]) {
    if (random(0, 10) == 0) {
      prognum++;
      if (prognum == nprogs) prognum = 0;
      prog = progs[prognum];
    }
    frame = 0;
  }
}

void setup() {
  cli();
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(OE, OUTPUT);
  for (int i = 0; i < NLAYERS; i++) {
    pinMode(g[i], OUTPUT);
  }
  digitalWrite(OE, LOW);
  randomSeed(analogRead(0));
  setupTimer();
}

int plane = 0;

void loop() {
  short val = prog[frame * NLAYERS + plane + 1];
  shiftOut(DATA, CLK, MSBFIRST, val >> 8);
  shiftOut(DATA, CLK, MSBFIRST, val);
  digitalWrite(LATCH, HIGH);
  // may need a several us delay here or just wire RCLK to SCLK
  delayMicroseconds(50);
  digitalWrite(LATCH, LOW);
  digitalWrite(g[plane], HIGH);
  delay(1);
  digitalWrite(g[plane], LOW);
  delayMicroseconds(50);
  plane++;
  if (plane == NLAYERS) plane = 0;
}
