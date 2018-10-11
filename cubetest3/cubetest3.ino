#define NCOLS 9
#define NLAYERS 3

#define CLK 2
#define DATA 3
#define LATCH 4
#define OE 5

// shift out two bytes
short l[] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080, 0x0100};
short g[] = {6, 7, 8};

void setup() {
  pinMode(CLK, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(OE, OUTPUT);
  for (int i = 0; i < NLAYERS; i++) {
    pinMode(g[i], OUTPUT);
  }
  digitalWrite(OE, LOW);

  short val = l[8];
  shiftOut(DATA, CLK, MSBFIRST, val >> 8);
  shiftOut(DATA, CLK, MSBFIRST, val);
  digitalWrite(LATCH, HIGH);
  delayMicroseconds(50);
  digitalWrite(LATCH, LOW);
}

int plane = 0;

void loop() {
  digitalWrite(g[plane], LOW);
  delay(3000);
  digitalWrite(g[plane], HIGH);
  plane++;
  if (plane == NLAYERS) plane = 0;
}
