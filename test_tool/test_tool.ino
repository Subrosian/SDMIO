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

const int buttonControl1L = 16;
const int buttonControl1S = 17;
const int buttonControl1R = 18;
const int buttonControl2L = 19;
const int buttonControl2S = 20;
const int buttonControl2R = 21;
const int buttonPad1L = 22;
const int buttonPad1R = 23;
const int buttonPad1U = 24;
const int buttonPad1D = 25;
const int buttonPad2L = 26;
const int buttonPad2R = 27;
const int buttonPad2U = 28;
const int buttonPad2D = 29;

const int buttonBack = 30;
const int buttonConfig = 32;

const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("INFO: Microcontroller Initialized");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  
  pinMode(pacMarqueeUL, INPUT_PULLUP);
  pinMode(pacMarqueeUR, INPUT_PULLUP);
  pinMode(pacMarqueeLL, INPUT_PULLUP);
  pinMode(pacMarqueeLR, INPUT_PULLUP);
  pinMode(pacSubs, INPUT_PULLUP);
  pinMode(pacPad1L, INPUT_PULLUP);
  pinMode(pacPad1R, INPUT_PULLUP);
  pinMode(pacPad1U, INPUT_PULLUP);
  pinMode(pacPad1D, INPUT_PULLUP);
  pinMode(pacControl1, INPUT_PULLUP);
  pinMode(pacPad2L, INPUT_PULLUP);
  pinMode(pacPad2R, INPUT_PULLUP);
  pinMode(pacPad2U, INPUT_PULLUP);
  pinMode(pacPad2D, INPUT_PULLUP);
  pinMode(pacControl2, INPUT_PULLUP);
  
  pinMode(buttonControl1L, INPUT_PULLUP);
  pinMode(buttonControl1S, INPUT_PULLUP);
  pinMode(buttonControl1R, INPUT_PULLUP);
  pinMode(buttonControl2L, INPUT_PULLUP);
  pinMode(buttonControl2S, INPUT_PULLUP);
  pinMode(buttonControl2R, INPUT_PULLUP);
  pinMode(buttonPad1L, INPUT_PULLUP);
  pinMode(buttonPad1R, INPUT_PULLUP);
  pinMode(buttonPad1U, INPUT_PULLUP);
  pinMode(buttonPad1D, INPUT_PULLUP);
  pinMode(buttonPad2L, INPUT_PULLUP);
  pinMode(buttonPad2R, INPUT_PULLUP);
  pinMode(buttonPad2U, INPUT_PULLUP);
  pinMode(buttonPad2D, INPUT_PULLUP);

  pinMode(buttonBack, INPUT_PULLUP);
  pinMode(buttonConfig, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(pacMarqueeUL) == HIGH) {
    Serial.println("INFO: pacMarqueeUL is HIGH");
  } else {
    Serial.println("INFO: pacMarqueeUL is LOW");
  }
}
