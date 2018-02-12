

#include <Adafruit_DotStar.h>
#include <SPI.h>         // COMMENT OUT THIS LINE FOR GEMMA OR TRINKET

#define NUMPIXELS 121 // Number of LEDs in strip
#define DATAPIN    11
#define CLOCKPIN   13
#define spotMaxTime 3000 //3000 = 3 secs

Adafruit_DotStar strip = Adafruit_DotStar(
  NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

unsigned long lastbutton = 0;

const int maxButtons = 9;
const int maxLigthts = 10;

//this is only declared for your convinience for referencing instead of using 0,1,2,3,4,5,6,7....
enum buttons {
  Left1Button,
  Select1Button,
  Right1Button,
  Left2Button,
  Select2Button,
  Right2Button,
  BackButton,
  UtilityButton,
  PowerButton,
};

enum spots {
  TL=6,
  TR=7,
  BL=8,
  BR=9,
};

typedef struct {
  byte microInput;
  byte oldState;
  byte usbButton;
} inputRef;


byte DDRLiGHTS[maxLigthts];

inputRef DDRButtons[maxButtons];

uint32_t color[NUMPIXELS-1];

unsigned long SPOTRT[4];
byte SEIZUREALERT=0;
 byte oldB=0;
void setup() {

  DDRButtons[Left1Button].microInput = 2;
  DDRButtons[Left1Button].usbButton = 1;
  DDRLiGHTS[Left1Button]=14;
  //DDRButtons[Left1Button].LED = 14;

  DDRButtons[Select1Button].microInput = 9;
  DDRButtons[Select1Button].usbButton = 2;
  DDRLiGHTS[Select1Button]=15;
  //DDRButtons[Select1Button].LED = 15;

  DDRButtons[Right1Button].microInput = 10;
  DDRButtons[Right1Button].usbButton = 3;
  DDRLiGHTS[Right1Button]=16;
  //DDRButtons[Right1Button].LED = 16;

  DDRButtons[Left2Button].microInput = 1;
  DDRButtons[Left2Button].usbButton = 4;
  DDRLiGHTS[Left2Button]=17;
  //[Left2Button].LED = 17;

  DDRButtons[Select2Button].microInput = 12;
  DDRButtons[Select2Button].usbButton = 5;
  DDRLiGHTS[Select2Button]=18;
  //DDRButtons[Select2Button].LED = 18;

  DDRButtons[Right2Button].microInput = 23;
  DDRButtons[Right2Button].usbButton = 6;
  DDRLiGHTS[Right2Button]=19;
  //DDRButtons[Right2Button].LED = 19;

  DDRButtons[BackButton].microInput = 22;
  DDRButtons[BackButton].usbButton = 7;

  DDRButtons[UtilityButton].microInput = 21;
  DDRButtons[UtilityButton].usbButton = 8;

  DDRButtons[PowerButton].microInput = 20;
  DDRButtons[PowerButton].usbButton = 9;

  DDRLiGHTS[TL]=3;
  DDRLiGHTS[TR]=4;
  DDRLiGHTS[BL]=5;
  DDRLiGHTS[BR]=6;
  
  //pinMode(6, OUTPUT);

  oldB=(LOW==digitalRead(21));
  delay(1000);
  Serial.begin(115200);
  strip.begin(); // Initialize pins for output
  strip.show();  // Turn all LEDs off ASAP
  
  //setup all the buttons as inputs and leds as outputs
  for (int counter = 0; counter < maxButtons; counter++) {
    pinMode(DDRButtons[counter].microInput, INPUT);
  }
  
  for (int counter = 0; counter < maxLigthts; counter++) {
    pinMode(DDRLiGHTS[counter], OUTPUT);
  }


  //collect all initial input values
  for (int counter = 0; counter < maxButtons; counter++) {
    DDRButtons[counter].oldState = digitalRead(DDRButtons[counter].microInput);
  }
  
  //all leds on
  for (int counter = 0; counter < maxLigthts; counter++) {
    digitalWrite(DDRLiGHTS[counter], HIGH);
  }
  
  delay(1000);

  //all leds off
  for (int counter = 0; counter < maxLigthts; counter++) {
    digitalWrite(DDRLiGHTS[counter], LOW);
  }
}

byte temp=0;
  

void loop() {
  
  if(LOW==digitalRead(21)){
     SEIZUREALERT=!SEIZUREALERT; 
     while(LOW==digitalRead(21)){}
     delay(250);
  }

  
  for(int counter=0;counter<4;counter++){
    if((unsigned long)(millis() - SPOTRT[counter] ) >= spotMaxTime){ //on too long turn off
      digitalWrite(DDRLiGHTS[counter+6], LOW); 
    }
  }
  
  if(!SEIZUREALERT){
    if(Serial.available()){
      if (Serial.read() == '$') {
        
        //get strip data
        for (int counter = 0; counter<108; counter++) {
            while (Serial.available() == 0) {  
              for(int counter=0;counter<4;counter++){
                if((unsigned long)(millis() - SPOTRT[counter] ) >= spotMaxTime){ //on too long turn off
                  digitalWrite(DDRLiGHTS[counter+6], LOW); 
                }
              }
            }
          color[counter] = Serial.read();
                      while (Serial.available() == 0) {  
              for(int counter=0;counter<4;counter++){
                if((unsigned long)(millis() - SPOTRT[counter] ) >= spotMaxTime){ //on too long turn off
                  digitalWrite(DDRLiGHTS[counter+6], LOW); 
                }
              }
            }
          color[counter] = ((unsigned)color[counter]<<8) + ((unsigned)Serial.read()<<16);
                      while (Serial.available() == 0) {  
              for(int counter=0;counter<4;counter++){
                if((unsigned long)(millis() - SPOTRT[counter] ) >= spotMaxTime){ //on too long turn off
                  digitalWrite(DDRLiGHTS[counter+6], LOW); 
                }
              }
            }
          color[counter] = color[counter] + Serial.read();
        }
        
        //first 8 button lights
                  while (Serial.available() == 0) {  
              for(int counter=0;counter<4;counter++){ 
                if((unsigned long)(millis() - SPOTRT[counter] ) >= spotMaxTime){ //on too long turn off
                  digitalWrite(DDRLiGHTS[counter+6], LOW); 
                }
              }
            }
        temp=Serial.read();
        for (int counter = 0; counter < 8; counter++) {
          if(counter<6 && !digitalRead(DDRButtons[counter].microInput)){
            digitalWrite(DDRLiGHTS[counter], HIGH);
          }else{   
            digitalWrite(DDRLiGHTS[counter], (temp&(1<<counter)));
          }
          if(counter>5 && (temp&(1<<counter))){ //spotlight check if light take time first 2
            SPOTRT[counter-6]=millis();
          }
        }
        
        //last 2
                  while (Serial.available() == 0) {  
              for(int counter=0;counter<4;counter++){
                if((unsigned long)(millis() - SPOTRT[counter] ) >= spotMaxTime){ //on too long turn off
                  digitalWrite(DDRLiGHTS[counter+6], LOW); 
                }
              }
            }
        temp=Serial.read();
        for (int counter = 0; counter < 2; counter++) {
          digitalWrite(DDRLiGHTS[counter+8], (temp&(1<<counter)));
          if(temp&(1<<counter)){ //spotlight check if light take time last 2
            SPOTRT[counter+2]=millis();
          }
        }
        
        for (int counter = 0; counter<108; counter++) {
          strip.setPixelColor(counter, color[counter]); 
        }
        strip.show();  
      }
    }
  }else{
    for (int counter = 0; counter < maxLigthts; counter++) {
      digitalWrite(DDRLiGHTS[counter], LOW);
    }
      strip.begin(); // Initialize pins for output
         for (int counter = 0; counter<108; counter++) {
          strip.setPixelColor(counter, 0x00); 
        }
        strip.show();  
  }
  //check all the buttons
  for (int counter = 0; counter < maxButtons; counter++) {
    //if oldstate does NOT !equal new readstate do something
    if (DDRButtons[counter].oldState != digitalRead(DDRButtons[counter].microInput)) {

      //save new old value
      DDRButtons[counter].oldState = digitalRead(DDRButtons[counter].microInput);
      
      //send button state to joystick using oposite new oldstate since !(HIGH=1)=0 and !(LOW=0)=1
      Joystick.button(DDRButtons[counter].usbButton, !DDRButtons[counter].oldState);
          //write led oposite state with read state using ! not symbol so LOW=HIGH and HIGH=LOW
      delay(100);
      if(counter<6 && (!SEIZUREALERT)){
        digitalWrite(DDRLiGHTS[counter], !DDRButtons[counter].oldState);
      }    
    }
    
    }
}

