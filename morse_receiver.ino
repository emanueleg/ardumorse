#define MORSE_SAMPLES 20
#define MORSE_DELAY 1
#define SYMBOL_T  MORSE_SAMPLES*MORSE_DELAY
#define ERR_MARGIN 0.6
#define N_TRESHOLD  1.05

#define DOT_T 200


#define DOT     ERR_MARGIN * DOT_T/SYMBOL_T
#define LINE    ERR_MARGIN * 3*DOT_T/SYMBOL_T
#define ELEMENT ERR_MARGIN * DOT_T/SYMBOL_T
#define CHAR    ERR_MARGIN * 3*DOT_T/SYMBOL_T
#define WORD    ERR_MARGIN * 7*DOT_T/SYMBOL_T

const int aPin =  A2;
char morse[128] = {0};

int val = 0;
int n_floor = 0;
int count = 0; int status;
int space = 0;
int mychar = 1;

void setup() {
  pinMode(aPin, INPUT);
  setMorse2Char();
  Serial.begin(115200);
  n_floor =  measure_noise_foor(100, 50);  // 100 samples, 50 ms
  Serial.print("Average value "); Serial.println(n_floor);

}

void loop() {
  val = readMic();

  if (val > n_floor) {
    if (status == LOW) {
      if (count > CHAR && mychar > 1) {
        // This is a CHAR
        Serial.print(morse[mychar]);
        if (count > 2.0*WORD) {
          // This is a SPACE
          Serial.print(" ");
        }
        mychar = 1;
      } else if (count < DOT/2) {
        // just noise - do nothing
      } else {
        // This is an ELEMENT - go on decoding char
      }
      count = 0;
    } else {
      // still decoding
    }
    status = HIGH;
    count += 1;
  } else {
    if (status == HIGH) {
      if (count > LINE) {
        // This is a LINE
        mychar = mychar << 1;
        mychar += 1;
      } else if (count < DOT/2) {
        // just noise - do nothing
      } else {
        // This is a DOT
        mychar = mychar << 1;
      }
      count = 0;
    } else {
      // still silent
      count += 1;
      if (count > 3*WORD && mychar > 1) {
        Serial.println(morse[mychar]);
        mychar = 1;
      }
    }

    status = LOW;
  }
}

int readMic() {
  int val = 0; int max = 0;
  int n = MORSE_SAMPLES; int t = MORSE_DELAY;

  for (int i = 0; i < n; i++) {
    val = analogRead(aPin);
    if (val > max) {
      max = val;
    }
    delay(t);
  }

  return max;
}

// dot -> 0   line -> 1   (first 1 is ignored)
void setMorse2Char() {
  morse[0b101] = 'A';
  morse[0b11000] = 'B';
  morse[0b11010] = 'C';
  morse[0b1100] = 'D';
  morse[0b10] = 'E';
  morse[0b10010] = 'F';
  morse[0b1110] = 'G';
  morse[0b10000] = 'H';
  morse[0b100] = 'I';
  morse[0b10111] = 'J';
  morse[0b1101] = 'K';
  morse[0b10100] = 'L';
  morse[0b111] = 'M';
  morse[0b110] = 'N';
  morse[0b1111] = 'O';
  morse[0b10110] = 'P';
  morse[0b11101] = 'Q';
  morse[0b1010] = 'R';
  morse[0b1000] = 'S';
  morse[0b11] = 'T';
  morse[0b1001] = 'U';
  morse[0b10001] = 'V';
  morse[0b1011] = 'W';
  morse[0b11001] = 'X';
  morse[0b11011] = 'Y';
  morse[0b11100] = 'Z';
  morse[0b111111] = '0';
  morse[0b101111] = '1';
  morse[0b100111] = '2';
  morse[0b100011] = '3';
  morse[0b100001] = '4';
  morse[0b100000] = '5';
  morse[0b110000] = '6';
  morse[0b111000] = '7';
  morse[0b111100] = '8';
  morse[0b111110] = '9';
}

int measure_noise_foor (int samples, int period) {
  long noise_sum = 0; int noise;
  for (int i = 0; i < samples; i++) {
    noise_sum += analogRead(aPin);
    delay(period);
  }
  noise = int(noise_sum / samples);
  n_floor = floor(noise * N_TRESHOLD);
  return n_floor;
}
