#define NCOLS 9
#define NLAYERS 3
int led_pins[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
int gnd_pins[] = {12, 11, 10};

#define DELAY 0

void setup() {
  for (int i = 0; i < NCOLS; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
  for (int i = 0; i < NLAYERS; i++) {
    pinMode(gnd_pins[i], OUTPUT);
  }
  digitalWrite(gnd_pins[0], HIGH);
}

int col = 0, plane = 0;

void loop() {
  digitalWrite(gnd_pins[plane], HIGH);
  digitalWrite(led_pins[col], HIGH);
  delay(DELAY);
  digitalWrite(led_pins[col], LOW);
  
  col++;
  if (col == NCOLS) {
    col = 0;
    digitalWrite(gnd_pins[plane], LOW);
    plane++;
    if (plane == NLAYERS) {
      plane = 0;
    }
  }
}
