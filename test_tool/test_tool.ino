// Christopher McKinzie (subrosian@gmail.com)

const int pacInputNum = 16;

enum pacInput {
  pacNull,
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
  byte onOff;
} pacRef;

pacRef pac[pacInputNum];

const int buttonInputNum = 17;

enum buttonInput {
  buttonNull,
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
  pac[pacMarqueeUL].microInput = 1;
  pac[pacMarqueeUR].microInput = 2;
  pac[pacMarqueeLL].microInput = 3;
  pac[pacMarqueeLR].microInput = 4;
  pac[pacSubs].microInput = 5;
  pac[pacPad1L].microInput = 6;
  pac[pacPad1R].microInput = 7;
  pac[pacPad1U].microInput = 8;
  pac[pacPad1D].microInput = 9;
  pac[pacControl1].microInput = 10;
  pac[pacPad2L].microInput = 11;
  pac[pacPad2R].microInput = 12;
  pac[pacPad2U].microInput = 14;
  pac[pacPad2D].microInput = 15;
  pac[pacControl2].microInput = 16;

  button[buttonControl1L].microInput = 17;
  button[buttonControl1L].usbButton = 1;

  button[buttonControl1S].microInput = 18;
  button[buttonControl1S].usbButton = 2;

  button[buttonControl1R].microInput = 19;
  button[buttonControl1R].usbButton = 3;

  button[buttonControl2L].microInput = 20;
  button[buttonControl2L].usbButton = 4;

  button[buttonControl2S].microInput = 21;
  button[buttonControl2S].usbButton = 5;

  button[buttonControl2R].microInput = 22;
  button[buttonControl2R].usbButton = 6;

  button[buttonPad1L].microInput = 23;
  button[buttonPad1L].usbButton = 7;

  button[buttonPad1R].microInput = 24;
  button[buttonPad1R].usbButton = 8;

  button[buttonPad1U].microInput = 25;
  button[buttonPad1U].usbButton = 9;

  button[buttonPad1D].microInput = 26;
  button[buttonPad1D].usbButton = 10;

  button[buttonPad2L].microInput = 27;
  button[buttonPad2L].usbButton = 11;

  button[buttonPad2R].microInput = 28;
  button[buttonPad2R].usbButton = 12;

  button[buttonPad2U].microInput = 29;
  button[buttonPad2U].usbButton = 13;

  button[buttonPad2D].microInput = 30;
  button[buttonPad2D].usbButton = 14;

  button[buttonBack].microInput = 31;
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
    int temp = digitalRead(pac[counter].microInput);
    if (pac[counter].oldState != temp) {

      //save new old value
      pac[counter].oldState = temp;

      if (temp == 0) {
        pac[counter].onOff = 1;
      }
      if (temp == 1) {
        pac[counter].onOff = 0;
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
      
      //   Serial.print("INFO: ");
      //   Serial.print(counter);
      //   Serial.print(" is ");
      //   Serial.println(temp);

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
