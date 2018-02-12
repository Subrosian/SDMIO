// Christopher McKinzie (subrosian@gmail.com)

const int pacMarqueeUL = 0;
const int pacMarqueeUR = 1;
const int pacMarqueeLL = 2;
const int pacMarqueeLR = 3;
const int pacSubs = 4;
const int pacPad1L = 5;
const int pacPad1R = 6;
const int pacPad1U = 7;
const int pacPad1D = 8;
const int pacControl1 = 9;
const int pacPad2L = 10;
const int pacPad2R = 11;
const int pacPad2U = 12;
const int pacPad2D = 14;
const int pacControl2 = 15;

const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("INFO: Microcontroller Initialized");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  pinMode(pacMarqueeUL, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(pacMarqueeUL) == HIGH) {
    Serial.println("INFO: pacMarqueeUL is HIGH");
  } else {
    Serial.println("INFO: pacMarqueeUL is LOW");
  }
}
