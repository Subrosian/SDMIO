//SDMIO 1.1
//Christopher McKinzie (subrosian@gmail.com)
//Board Teensy 3.5
//USB Type Keyboard + Mouse + Joystick
//CPU Speed 120Mhz
//Optimise Faster
//Keyboard Layout English

#include <Adafruit_NeoPixel.h>

#define NUM_LEDS 492
#define DATA_PIN 39
//CRGB leds[NUM_LEDS];
Adafruit_NeoPixel leds = Adafruit_NeoPixel(NUM_LEDS, DATA_PIN, NEO_GRB + NEO_KHZ800);

unsigned long lastbutton = 0;
int attractmode = 0;
const int pacInputNum = 16;

#define shutdown_hold_time 5000
unsigned long held_timer;
bool blackout_mode = false;

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
  buttonConfig
};

typedef struct {
  byte microInput;
  byte oldState;
  byte usbButton;
} buttonRef;

buttonRef button[buttonInputNum];
const int lightOutputNum = 16;

enum lightOutput {
  lightNull,
  lightPad1L,
  lightPad1R,
  lightPad1U,
  lightPad1D,
  lightPad2L,
  lightPad2R,
  lightPad2U,
  lightPad2D,
  lightMarqueeUL,
  lightMarqueeUR,
  lightMarqueeLL,
  lightMarqueeLR,
  lightControl1,
  lightControl2,
  lightSubs,
};

typedef struct {
  int16_t firstLed;
  int16_t numLeds;
  uint32_t fill_color;
  byte oldState;
  byte onOff;
} lightRef;

lightRef light[lightOutputNum];
const int ledPin = 13;
int randomNumber;

void setup() {
  //FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);

  pac[pacPad1L].microInput = 26;
  pac[pacPad1R].microInput = 25;
  pac[pacPad1U].microInput = 24;
  pac[pacPad1D].microInput = 12;
  pac[pacPad2L].microInput = 11;
  pac[pacPad2R].microInput = 10;
  pac[pacPad2U].microInput = 9;
  pac[pacPad2D].microInput = 8;
  pac[pacMarqueeUL].microInput = 7;
  pac[pacMarqueeUR].microInput = 6;
  pac[pacMarqueeLL].microInput = 5;
  pac[pacMarqueeLR].microInput = 4;
  pac[pacControl1].microInput = 3;
  pac[pacControl2].microInput = 2;
  pac[pacSubs].microInput = 1;

  button[buttonPad1L].microInput = 28;
  button[buttonPad1L].usbButton = 1;
  button[buttonPad1R].microInput = 21;
  button[buttonPad1R].usbButton = 2;
  button[buttonPad1U].microInput = 27;
  button[buttonPad1U].usbButton = 3;
  button[buttonPad1D].microInput = 22;
  button[buttonPad1D].usbButton = 4;
  button[buttonPad2L].microInput = 16;
  button[buttonPad2L].usbButton = 5;
  button[buttonPad2R].microInput = 15;
  button[buttonPad2R].usbButton = 6;
  button[buttonPad2U].microInput = 32;
  button[buttonPad2U].usbButton = 7;
  button[buttonPad2D].microInput = 17;
  button[buttonPad2D].usbButton = 8;
  button[buttonControl1L].microInput = 30;
  button[buttonControl1L].usbButton = 9;
  button[buttonControl1S].microInput = 31;
  button[buttonControl1S].usbButton = 10;
  button[buttonControl1R].microInput = 19;
  button[buttonControl1R].usbButton = 11;
  button[buttonControl2L].microInput = 36;
  button[buttonControl2L].usbButton = 12;
  button[buttonControl2S].microInput = 34;
  button[buttonControl2S].usbButton = 13;
  button[buttonControl2R].microInput = 35;
  button[buttonControl2R].usbButton = 14;
  button[buttonBack].microInput = 18;
  button[buttonBack].usbButton = 15;
  button[buttonConfig].microInput = 33;
  button[buttonConfig].usbButton = 16;

  light[lightMarqueeUL].firstLed = 0;
  light[lightMarqueeUL].numLeds = 12;
  light[lightMarqueeUR].firstLed = 12;
  light[lightMarqueeUR].numLeds = 12;
  light[lightMarqueeLL].firstLed = 24;
  light[lightMarqueeLL].numLeds = 12;
  light[lightMarqueeLR].firstLed = 36;
  light[lightMarqueeLR].numLeds = 12;

  light[pacControl1].firstLed = 350;
  light[pacControl1].numLeds = 1;
  light[pacControl2].firstLed = 351;
  light[pacControl2].numLeds = 1;
  light[pacSubs].firstLed = 54;
  light[pacSubs].numLeds = 104;

  light[lightPad1U].firstLed = 158;
  light[lightPad1U].numLeds = 24;
  light[lightPad1D].firstLed = 182;
  light[lightPad1D].numLeds = 24;
  light[lightPad1L].firstLed = 206;
  light[lightPad1L].numLeds = 24;
  light[lightPad1R].firstLed = 230;
  light[lightPad1R].numLeds = 24;

  light[lightPad2U].firstLed = 254;
  light[lightPad2U].numLeds = 24;
  light[lightPad2D].firstLed = 278;
  light[lightPad2D].numLeds = 24;
  light[lightPad2L].firstLed = 302;
  light[lightPad2L].numLeds = 24;
  light[lightPad2R].firstLed = 326;
  light[lightPad2R].numLeds = 24;

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
  leds.begin();
}

int reDraw=0;

void fadeLeds(){
  uint8_t r,g,b;
  for(int x=0;x<NUM_LEDS;x++){
    r=(leds.getPixelColor(x) >> 16);
    g=(leds.getPixelColor(x) >> 8);
    b=(leds.getPixelColor(x));
    if(r > 0){
      r = int(r *0.90);
    }
    if(g> 0){
      g = int(g *0.90);
    }
    if(b > 0){
      b = int(b *0.90);
    }
    leds.setPixelColor(x,r,g,b);
  }
}

void HSV_to_RGB(float h, float s, float v, byte *r, byte *g, byte *b)
{
  int i;
  float f,p,q,t;
  h = max(0.0, min(360.0, h));
  s = max(0.0, min(100.0, s));
  v = max(0.0, min(100.0, v));
  s /= 100;
  v /= 100;
  if(s == 0) {
    // Achromatic (grey)
    *r = *g = *b = round(v*255);
    return;
  }
  h /= 60; // sector 0 to 5
  i = floor(h);
  f = h - i; // factorial part of h
  p = v * (1 - s);
  q = v * (1 - s * f);
  t = v * (1 - s * (1 - f));
  switch(i) {
    case 0:
      *r = round(255*v);
      *g = round(255*t);
      *b = round(255*p);
      break;
    case 1:
      *r = round(255*q);
      *g = round(255*v);
      *b = round(255*p);
      break;
    case 2:
      *r = round(255*p);
      *g = round(255*v);
      *b = round(255*t);
      break;
    case 3:
      *r = round(255*p);
      *g = round(255*q);
      *b = round(255*v);
      break;
    case 4:
      *r = round(255*t);
      *g = round(255*p);
      *b = round(255*v);
      break;
    default: // case 5:
      *r = round(255*v);
      *g = round(255*p);
      *b = round(255*q);
    }
}

void loop() {

  //reset redraw value and check for changes
  reDraw=0;
  static bool current_pin_state;
  static uint8_t r,g,b;

  //check all the pacinputs
  for (int counter = 0; counter < pacInputNum; counter++) {

    //if oldstate does NOT !equal new readstate do something
    current_pin_state = digitalRead(pac[counter].microInput);

    //always set pin to untriggered if blackoutmode
    if(blackout_mode){

      switch(counter){
        case pacSubs:
        case pacMarqueeUL:
        case pacMarqueeUR:
        case pacMarqueeLL:
        case pacMarqueeLR:
          current_pin_state = 1;
        break; 
      }

    }

    if (pac[counter].oldState != current_pin_state) {
      //change in input update leds
      reDraw=1;

      pac[counter].oldState = current_pin_state;

      if (!current_pin_state) {

        //r=g=b=0;

        HSV_to_RGB((random(360)/360.0)*360.0,100.0f,50.0f,&r,&g,&b);

        light[counter].fill_color = leds.Color(r,g,b);
        pac[counter].onOff = !current_pin_state;

        for (int16_t ledCounter = light[counter].firstLed; ledCounter < light[counter].firstLed + light[counter].numLeds; ledCounter++) {
          //leds[ledCounter] = CRGB::Black;
          leds.setPixelColor(ledCounter, light[counter].fill_color);
        }        

      }

    }else if(!current_pin_state){//if pac pad button pressed hold color

      switch(counter){
        case pacPad1L:
        case pacPad1R:
        case pacPad1U:
        case pacPad1D:
        case pacPad2L:
        case pacPad2R:
        case pacPad2U:
        case pacPad2D:

          for (int16_t ledCounter = light[counter].firstLed; ledCounter < light[counter].firstLed + light[counter].numLeds; ledCounter++) {
            //leds[ledCounter] = CRGB::Black;
            leds.setPixelColor(ledCounter, light[counter].fill_color);
          }

        break;
      }

    }

  }

  //needs a redraw
  fadeLeds();
  if(reDraw==1 or 1){
    //FastLED.show();
    leds.show();
    reDraw=0;
  }

  //check all the buttons
  for (int counter = 1; counter < buttonInputNum; counter++) {
    //if oldstate does NOT !equal new readstate do something
    if (button[counter].oldState != digitalRead(button[counter].microInput)) {
      button[counter].oldState = digitalRead(button[counter].microInput);

      if(counter==buttonConfig){

        if(!button[counter].oldState){ //if held

          held_timer=millis();
          blackout_mode = !blackout_mode;

        }

      }else{

        //send button state to joystick using oposite new oldstate since !(HIGH=1)=0 and !(LOW=0)=1
        Joystick.button(button[counter].usbButton, !button[counter].oldState);
      }

    }

  }

  if(!button[buttonConfig].oldState && (held_timer+shutdown_hold_time)<millis()){ //if held for shutdown time

    Keyboard.press(KEY_SYSTEM_POWER_DOWN);
    Keyboard.release(KEY_SYSTEM_POWER_DOWN);

  }

}
