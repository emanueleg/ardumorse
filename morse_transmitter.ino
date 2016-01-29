#define BUZZER_VOLUME 4

#define DOT_T 200


#define DOT DOT_T
#define LINE  3*DOT
#define ELEMENT  DOT
#define CHAR  3*DOT
#define WORD  7*DOT

int morse[128] = {0};

int buzzerPin = 6;
int speed = DOT;

void setup() {
  pinMode(buzzerPin, OUTPUT);
  setChar2Morse();
  Serial.begin(115200);
}

void loop() {
  if (Serial.available() > 0) {
    int in = Serial.read();
    in = toupper(in);
    if (isalnum(in)) {
      transmit(in);
    } else if (in == ' ') {
      delay(WORD);
    }
  }
}

void transmit(char c) {
  int val = morse[c];

  // reverse bits (we transmit left to right!)
  int rval = 1; int tv = val;
  while (tv > 1) {
    rval = rval << 1;
    rval = rval + (tv - (tv & 0xfe));
    tv = tv >> 1;
  }
  val = rval;

  // transmit characters
  while (val > 1) {
    int s = val - (val & 0xfe);
    if (s == 1) {
      beep(LINE);
    } else {
      beep(DOT);
    }
    delay(ELEMENT);
    //Serial.println(val, BIN);
    val = val >> 1;
  }
  delay(CHAR);
}

void beep(int delayms) {
  analogWrite(buzzerPin, BUZZER_VOLUME);
  delay(delayms);
  analogWrite(buzzerPin ,0);      
}

// dot -> 0   line -> 1   (first 1 is ignored)
void setChar2Morse() {
  morse['A'] = 0b101;
  morse['B'] = 0b11000;
  morse['C'] = 0b11010;
  morse['D'] = 0b1100;
  morse['E'] = 0b10;
  morse['F'] = 0b10010;
  morse['G'] = 0b1110;
  morse['H'] = 0b10000;
  morse['I'] = 0b100;
  morse['J'] = 0b10111;
  morse['K'] = 0b1101;
  morse['L'] = 0b10100;
  morse['M'] = 0b111;
  morse['N'] = 0b110;
  morse['O'] = 0b1111;
  morse['P'] = 0b10110;
  morse['Q'] = 0b11101;
  morse['R'] = 0b1010;
  morse['S'] = 0b1000;
  morse['T'] = 0b11;
  morse['U'] = 0b1001;
  morse['V'] = 0b10001;
  morse['W'] = 0b1011;
  morse['X'] = 0b11001;
  morse['Y'] = 0b11011;
  morse['Z'] = 0b11100;
  morse['0'] = 0b111111;
  morse['1'] = 0b101111;
  morse['2'] = 0b100111;
  morse['3'] = 0b100011;
  morse['4'] = 0b100001;
  morse['5'] = 0b100000;
  morse['6'] = 0b110000;
  morse['7'] = 0b111000;
  morse['8'] = 0b111100;
  morse['9'] = 0b111110;
}
