// Christopher McKinzie (subrosian@gmail.com)

#include "FastLED.h"
#define NUM_LEDS 300
#define DATA_PIN 32
CRGB leds[NUM_LEDS];

const int pacInputNum = 16;

enum pacInput {
  pacNull,
  pacPad1L,
  pacPad1R,
  pacPad1U,
  pacPad1D,
  pacPad2L,
  pacPad2R,
  pacPad2U,
  pacPad2D,
  pacMarqueeUL,
  pacMarqueeUR,
  pacMarqueeLL,
  pacMarqueeLR,
  pacControl1,
  pacControl2,
  pacSubs,
};

typedef struct {
  byte microInput;
  byte oldState;
  byte onOff;
} pacRef;

pacRef pac[pacInputNum];

const int buttonInputNum = 17;

enum buttonInput {
  buttonNull,
  buttonPad1L,
  buttonPad1R,
  buttonPad1U,
  buttonPad1D,
  buttonPad2L,
  buttonPad2R,
  buttonPad2U,
  buttonPad2D,
  buttonControl1L,
  buttonControl1S,
  buttonControl1R,
  buttonControl2L,
  buttonControl2S,
  buttonControl2R,
  buttonBack,
  buttonConfig,
};

typedef struct {
  byte microInput;
  byte oldState;
  byte usbButton;
} buttonRef;

buttonRef button[buttonInputNum];

const int ledPin = 13;

void setup() {
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  pac[pacPad1L].microInput = 1;
  pac[pacPad1R].microInput = 2;
  pac[pacPad1U].microInput = 3;
  pac[pacPad1D].microInput = 4;
  pac[pacPad2L].microInput = 5;
  pac[pacPad2R].microInput = 6;
  pac[pacPad2U].microInput = 7;
  pac[pacPad2D].microInput = 8;
  pac[pacMarqueeUL].microInput = 9;
  pac[pacMarqueeUR].microInput = 10;
  pac[pacMarqueeLL].microInput = 11;
  pac[pacMarqueeLR].microInput = 12;
  pac[pacControl1].microInput = 14;
  pac[pacControl2].microInput = 15;
  pac[pacSubs].microInput = 16;

  button[buttonPad1L].microInput = 17;
  button[buttonPad1L].usbButton = 1;

  button[buttonPad1R].microInput = 18;
  button[buttonPad1R].usbButton = 2;

  button[buttonPad1U].microInput = 19;
  button[buttonPad1U].usbButton = 3;

  button[buttonPad1D].microInput = 20;
  button[buttonPad1D].usbButton = 4;

  button[buttonPad2L].microInput = 21;
  button[buttonPad2L].usbButton = 5;

  button[buttonPad2R].microInput = 22;
  button[buttonPad2R].usbButton = 6;

  button[buttonPad2U].microInput = 23;
  button[buttonPad2U].usbButton = 7;

  button[buttonPad2D].microInput = 24;
  button[buttonPad2D].usbButton = 8;

  button[buttonControl1L].microInput = 25;
  button[buttonControl1L].usbButton = 9;

  button[buttonControl1S].microInput = 26;
  button[buttonControl1S].usbButton = 10;

  button[buttonControl1R].microInput = 27;
  button[buttonControl1R].usbButton = 11;

  button[buttonControl2L].microInput = 28;
  button[buttonControl2L].usbButton = 12;

  button[buttonControl2S].microInput = 29;
  button[buttonControl2S].usbButton = 13;

  button[buttonControl2R].microInput = 30;
  button[buttonControl2R].usbButton = 14;

  button[buttonBack].microInput = 33;
  button[buttonBack].usbButton = 15;

  button[buttonConfig].microInput = 34;
  button[buttonConfig].usbButton = 16;

  Serial.begin(9600);
  Serial.println("INFO: Microcontroller Initialized");
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);

  //setup all pacinputs as inputs
  for (int counter = 0; counter < pacInputNum; counter++) {
    pinMode(pac[counter].microInput, INPUT_PULLUP);
  }

  //setup all the buttons as inputs
  for (int counter = 0; counter < buttonInputNum; counter++) {
    pinMode(button[counter].microInput, INPUT_PULLUP);
  }
}

void loop() {
  //check all the pacinputs
  for (int counter = 0; counter < pacInputNum; counter++) {
    //if oldstate does NOT !equal new readstate do something
    int temp = digitalRead(pac[counter].microInput);
    if (pac[counter].oldState != temp) {

      //save new old value
      pac[counter].oldState = temp;

      if (temp == 0) {
        pac[counter].onOff = 1;
        leds[counter] = CRGB::White;
      }
      if (temp == 1) {
        pac[counter].onOff = 0;
        leds[counter] = CRGB::Black;
      }
      Serial.print("INFO: ");
      Serial.print(pac[1].onOff);
      Serial.print(" ");
      Serial.print(pac[2].onOff);
      Serial.print(" ");
      Serial.print(pac[3].onOff);
      Serial.print(" ");
      Serial.print(pac[4].onOff);
      Serial.print(" | ");
      Serial.print(pac[5].onOff);
      Serial.print(" ");
      Serial.print(pac[6].onOff);
      Serial.print(" ");
      Serial.print(pac[7].onOff);
      Serial.print(" ");
      Serial.print(pac[8].onOff);
      Serial.print(" | ");
      Serial.print(pac[9].onOff);
      Serial.print(" ");
      Serial.print(pac[10].onOff);
      Serial.print(" ");
      Serial.print(pac[11].onOff);
      Serial.print(" ");
      Serial.print(pac[12].onOff);
      Serial.print(" | ");
      Serial.print(pac[13].onOff);
      Serial.print(" ");
      Serial.print(pac[14].onOff);
      Serial.print(" ");
      Serial.println(pac[15].onOff);
      FastLED.show();
    }
  }

  //check all the buttons
  for (int counter = 0; counter < buttonInputNum; counter++) {
    //if oldstate does NOT !equal new readstate do something
    int temp = digitalRead(button[counter].microInput);
    if (button[counter].oldState != temp) {

      //save new old value
      button[counter].oldState = temp;

      Serial.print("INFO: ");
      Serial.print(counter);
      Serial.print(" is ");
      Serial.println(temp);
      //send button state to joystick using oposite new oldstate since !(HIGH=1)=0 and !(LOW=0)=1
      //Joystick.button(button[counter].usbButton, !button[counter].oldState);
    }
  }
}
