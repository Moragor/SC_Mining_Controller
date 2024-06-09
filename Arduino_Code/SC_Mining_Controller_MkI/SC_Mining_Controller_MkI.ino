#include <Bounce2.h>
#include <Joystick.h>     //https://github.com/MHeironimus/ArduinoJoystickLibrary

#define laserPin 2       //0 (array position)
#define lModePin 3       //1
#define mod1Pin 4        //2
#define mod2Pin 5        //3
#define mod3Pin 6        //4
#define mModePin 7       //5
#define eStopPin 8       //6
#define joyButtonPin 14  //7
#define xAxisPin A0
#define yAxisPin A1
#define centerTapPin A2
#define sliderPin A10

byte buttonDelay = 25;
const int numButtons = 8;                                                                                                // Number of buttons
const int buttonPins[numButtons] = { laserPin, lModePin, mod1Pin, mod2Pin, mod3Pin, mModePin, eStopPin, joyButtonPin };  // Pin numbers for your buttons

Bounce debouncer[numButtons];  // Create a debouncer object for each button

//Setting up the features of the joystick
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                   7, 0,                  // Button Count, Hat Switch Count
                   true, true, true,      // X, Y and Z Axis
                   false, false, false,   // Rx, Ry and Rz Axis
                   false, false,          // Rudder and Throttle
                   false, false, false);  // Accelerator, Brake and Steering

void setup() {
  Joystick.setXAxisRange(0, 1023);  //Output range of the Joystick
  Joystick.setYAxisRange(0, 1023);
  Joystick.setZAxisRange(0, 1023);
  Joystick.begin();

  //Setting up the buttons with the debounce library
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);  // Set buttons as INPUT_PULLUP
    debouncer[i].attach(buttonPins[i]);
    debouncer[i].interval(5);  // Debounce interval in milliseconds
  }

  Serial.begin(9600);
}

void loop() {
  //Checking button state changes
  for (int i = 0; i < numButtons; i++) {
    debouncer[i].update();
  }

  //Buttons
  //Laser power
  if (debouncer[0].fell()) {    //.fell meands on button down
    Joystick.pressButton(0);
    delay(buttonDelay);
    Joystick.releaseButton(0);
  }
  //Laser mode
  if (debouncer[1].changed()) { //.changed means any change
    Joystick.pressButton(1);
    delay(buttonDelay);
    Joystick.releaseButton(1);
  }
  //Mod 1
  if (debouncer[2].fell()) {
    Joystick.pressButton(2);
    delay(buttonDelay);
    Joystick.releaseButton(2);
  }
  //Mod 2
  if (debouncer[3].fell()) {
    Joystick.pressButton(3);
    delay(buttonDelay);
    Joystick.releaseButton(3);
  }
  //Mod 3
  if (debouncer[4].fell()) {
    Joystick.pressButton(4);
    delay(buttonDelay);
    Joystick.releaseButton(4);
  }
  //Mining mode
  if (debouncer[5].changed()) {
    Joystick.pressButton(5);
    delay(buttonDelay);
    Joystick.releaseButton(5);
  }
  //E-Stop
  if (debouncer[6].fell()) {
    Joystick.pressButton(5);
    delay(buttonDelay);
    Joystick.releaseButton(5);
  }
  //Joystick button
  if (debouncer[7].fell()) {
    Joystick.pressButton(0);
    delay(buttonDelay);
    Joystick.releaseButton(0);
  }


  //Joystick and Slider output
  int xInput(analogRead(xAxisPin));
  xInput = map(xInput, 0, 1013, 0, 1023);
  Joystick.setXAxis(xInput);
  int yInput(analogRead(yAxisPin));
  yInput = map(yInput, 5, 1017, 0, 1023);
  Joystick.setYAxis(yInput);
  Joystick.setZAxis(analogRead(sliderPin));
}


