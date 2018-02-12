unsigned long attractdelay = 10000;
unsigned long lastbutton = 0;
unsigned long attracttimer = 250;
unsigned long lastattract = 0;

long attractmode = 0;
long randNumber = 14;
long randNumberplus;

const int TESTLED =  13;

const int maxButtons = 8;

//this is only declared for your convinience for referencing instead of using 0,1,2,3,4,5,6,7....
enum buttons {
  Left1Button,
  Right1Button,
  Up1Button,
  Down1Button,
  Left2Button,
  Right2Button,
  Up2Button,
  Down2Button
};

typedef struct {
  byte microInput;
  byte oldState;
  byte usbButton;
  byte LED;
} inputRef;


inputRef DDRButtons[maxButtons];

void setup() {

  DDRButtons[Left1Button].microInput = 0;
  DDRButtons[Left1Button].usbButton = 1;
  DDRButtons[Left1Button].LED = 14;

  DDRButtons[Right1Button].microInput = 3;
  DDRButtons[Right1Button].usbButton = 4;
  DDRButtons[Right1Button].LED = 17;

  DDRButtons[Up1Button].microInput = 2;
  DDRButtons[Up1Button].usbButton = 3;
  DDRButtons[Up1Button].LED = 16;

  DDRButtons[Down1Button].microInput = 1;
  DDRButtons[Down1Button].usbButton = 2;
  DDRButtons[Down1Button].LED = 15;

  DDRButtons[Left2Button].microInput = 8;
  DDRButtons[Left2Button].usbButton = 5;
  DDRButtons[Left2Button].LED = 18;

  DDRButtons[Right2Button].microInput = 11;
  DDRButtons[Right2Button].usbButton = 8;
  DDRButtons[Right2Button].LED = 21;

  DDRButtons[Up2Button].microInput = 10;
  DDRButtons[Up2Button].usbButton = 7;
  DDRButtons[Up2Button].LED = 20;

  DDRButtons[Down2Button].microInput = 9;
  DDRButtons[Down2Button].usbButton = 6;
  DDRButtons[Down2Button].LED = 19;

  delay(5000);
  Serial.begin(115200);

  //setup all the buttons as inputs and leds as outputs
  for (int counter = 0; counter < maxButtons; counter++) {
    pinMode(DDRButtons[counter].microInput, INPUT);
    pinMode(DDRButtons[counter].LED, OUTPUT);
  }

  //collect all initial input values
  for (int counter = 0; counter < maxButtons; counter++) {
    DDRButtons[counter].oldState = digitalRead(DDRButtons[counter].microInput);
  }

  pinMode(TESTLED, OUTPUT);
  digitalWrite(TESTLED, HIGH);

  //all leds on
  for (int counter = 0; counter < maxButtons; counter++) {
    digitalWrite(DDRButtons[counter].LED, HIGH);
  }

  delay(5000);

  //all leds off
  for (int counter = 0; counter < maxButtons; counter++) {
    digitalWrite(DDRButtons[counter].LED, LOW);
  }

}

void loop() {

  if ((unsigned long)(millis() - lastbutton ) >= attractdelay) {
    digitalWrite(TESTLED, LOW);
    attractmode = 1;
    if ((unsigned long)(millis() - lastattract ) >= attracttimer) {
      lastattract = millis();

      for (int counter = 0; counter < maxButtons; counter++) {
        digitalWrite(DDRButtons[counter].LED, LOW);
      }

      //randNumber = random(14, 18);
      digitalWrite(randNumber, HIGH);
      digitalWrite(randNumber + 4, HIGH);
      if (randNumber == 15) {
        randNumber = 14;
      }
      else if (randNumber == 17) {
        randNumber = 15;
      }
      else if (randNumber == 16) {
        randNumber = 17;
      }
      else if (randNumber == 14) {
        randNumber = 16;
      }
    }
  }
  else {
    digitalWrite(TESTLED, HIGH);
  }

  //check all the buttons
  for (int counter = 0; counter < maxButtons; counter++) {
    //if oldstate does NOT !equal new readstate do something
    if (DDRButtons[counter].oldState != digitalRead(DDRButtons[counter].microInput)) {

      lastbutton = millis();

      if (attractmode == 1) {
        attractmode = 0;
        //all leds off
        for (int counter = 0; counter < maxButtons; counter++) {
          digitalWrite(DDRButtons[counter].LED, LOW);

        }

      }

      //save new old value
      DDRButtons[counter].oldState = digitalRead(DDRButtons[counter].microInput);

      //write led oposite state with read state using ! not symbol so LOW=HIGH and HIGH=LOW
      digitalWrite(DDRButtons[counter].LED, !DDRButtons[counter].oldState);

      //send button state to joystick using oposite new oldstate since !(HIGH=1)=0 and !(LOW=0)=1
      Joystick.button(DDRButtons[counter].usbButton, !DDRButtons[counter].oldState);

    }
  }
}


