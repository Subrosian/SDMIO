// Christopher McKinzie (subrosian@gmail.com)

const int pacInputNum = 15;

enum pacInput {
  pacMarqueeUL,
  pacMarqueeUR,
  pacMarqueeLL,
  pacMarqueeLR,
  pacSubs,
  pacPad1L,
  pacPad1R,
  pacPad1U,
  pacPad1D,
  pacControl1,
  pacPad2L,
  pacPad2R,
  pacPad2U,
  pacPad2D,
  pacControl2,
};

typedef struct {
  byte microInput;
  byte oldState;
} pacRef;

pacRef pac[pacInputNum];

const int buttonInputNum = 16;

enum buttonInput {
  buttonControl1L,
  buttonControl1S,
  buttonControl1R,
  buttonControl2L,
  buttonControl2S,
  buttonControl2R,
  buttonPad1L,
  buttonPad1R,
  buttonPad1U,
  buttonPad1D,
  buttonPad2L,
  buttonPad2R,
  buttonPad2U,
  buttonPad2D,
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
  pac[pacMarqueeUL].microInput = 0;
  pac[pacMarqueeUR].microInput = 1;
  pac[pacMarqueeLL].microInput = 2;
  pac[pacMarqueeLR].microInput = 3;
  pac[pacSubs].microInput = 4;
  pac[pacPad1L].microInput = 5;
  pac[pacPad1R].microInput = 6;
  pac[pacPad1U].microInput = 7;
  pac[pacPad1D].microInput = 8;
  pac[pacControl1].microInput = 9;
  pac[pacPad2L].microInput = 10;
  pac[pacPad2R].microInput = 11;
  pac[pacPad2U].microInput = 12;
  pac[pacPad2D].microInput = 14;
  pac[pacControl2].microInput = 15;

  button[buttonControl1L].microInput = 16;
  button[buttonControl1L].usbButton = 1;

  button[buttonControl1S].microInput = 17;
  button[buttonControl1S].usbButton = 2;

  button[buttonControl1R].microInput = 18;
  button[buttonControl1R].usbButton = 3;

  button[buttonControl2L].microInput = 19;
  button[buttonControl2L].usbButton = 4;

  button[buttonControl2S].microInput = 20;
  button[buttonControl2S].usbButton = 5;

  button[buttonControl2R].microInput = 21;
  button[buttonControl2R].usbButton = 6;

  button[buttonPad1L].microInput = 22;
  button[buttonPad1L].usbButton = 7;

  button[buttonPad1R].microInput = 23;
  button[buttonPad1R].usbButton = 8;

  button[buttonPad1U].microInput = 24;
  button[buttonPad1U].usbButton = 9;

  button[buttonPad1D].microInput = 25;
  button[buttonPad1D].usbButton = 10;

  button[buttonPad2L].microInput = 26;
  button[buttonPad2L].usbButton = 11;

  button[buttonPad2R].microInput = 27;
  button[buttonPad2R].usbButton = 12;

  button[buttonPad2U].microInput = 28;
  button[buttonPad2U].usbButton = 13;

  button[buttonPad2D].microInput = 29;
  button[buttonPad2D].usbButton = 14;

  button[buttonBack].microInput = 30;
  button[buttonBack].usbButton = 15;

  button[buttonConfig].microInput = 32;
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
    if (pac[counter].oldState != digitalRead(pac[counter].microInput)) {

      //save new old value
      pac[counter].oldState = digitalRead(pac[counter].microInput);

      Serial.print("INFO:");
      Serial.print(counter);
      Serial.print(" is ");
      Serial.println(digitalRead(pac[counter].microInput));
    }
  }
  
  //check all the buttons
  for (int counter = 0; counter < buttonInputNum; counter++) {
    //if oldstate does NOT !equal new readstate do something
    if (button[counter].oldState != digitalRead(button[counter].microInput)) {

      //save new old value
      button[counter].oldState = digitalRead(button[counter].microInput);

      Serial.print("INFO:");
      Serial.print(counter);
      Serial.print(" is ");
      Serial.println(digitalRead(button[counter].microInput));
      //send button state to joystick using oposite new oldstate since !(HIGH=1)=0 and !(LOW=0)=1
      Joystick.button(button[counter].usbButton, !button[counter].oldState);
    }
  }
}
