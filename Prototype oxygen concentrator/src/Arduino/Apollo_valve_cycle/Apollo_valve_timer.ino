//    Valve cycling code for Project Apollo v1 prototype
//

//Libraries to be included:
// Install library Adafruit_GFX.h https://github.com/adafruit/Adafruit-GFX-Library
// Install library Adafruit_SSD1306.h  https://www.github.com/adafruit/Adafruit_SSD1306


// Connectivity:
// - Connect GND from Arduino to GND(-) on ULN2003 board
// - Connect Vin from Arudino to 12V(+) on ULN2003 board and to (+) of 2-way valve motor and to (+) of 5-way valve motor
// - Connect PIN 2 pin from Arduino to IN PIN 1 on ULN2003 board
// - Connect PIN 3 pin from Arduino to IN PIN 2 on ULN2003 board
// - Connect PIN 4 pin from Arduino to IN PIN 3 on ULN2003 board
// - Connect Pin A0 from Arduino to the Signal pin of the potentiometer for 5 way valve
// - connect Pin A1 from Arduino to the Signal pin of the potentiometer for 2 way valve
// - Connect Pin A4 to SDA of OLED screen
// - Connect Pin A5 to SCL of OLED screen
// - Connect OUT PIN 1 pin from ULN2003 board to (-) of 2-way valve
// - Connect OUT PIN 2 pin from ULN2003 board to (-) of 5-way valve
// - Connect OUT PIN 3 pin from ULN2003 board to (-) of fan
// - Program Arduino board
// - Verify that the LEDs blink in the right order
// - Connect 12V supply to Arduino (at least 1.5A current)
// - Verify that valves couple in the right order

//Libraries to be included

#include <Adafruit_GFX.h> //Turn on for OLED
#include <Adafruit_SSD1306.h> //Turn on for OLED
#include <Stepper.h>

//Turn on below for OLED
Adafruit_SSD1306 display(4); //defines the pin that data is sent through to the LCD on

//setup the stepper motor constants
//const int stepsPerRevolution = 2038; //need to test buy assuming research is correct that a 28BYJ-48 motor needs 2038 steps per turn
//Stepper stepper(stepsPerRevolution, 8, 10, 9, 11);

// Define the screen dimensions

//Turn on for OLED
#define SCREEN_WIDTH 128 // OLED display width in pixels
#define SCREEN_HEIGHT 64 // OLED display width in pixels

// PIN identifiers

//
// PIN 2 on Arduino Uno
// - To be connnected to INPUT PIN 1 on ULN2003 board
// - Which drives OUT PIN 1 on ULN2003 board
// - Which drives (-) on 2-way valve
//
int valve_2way = 2; //Green LED for debugging

//
// PIN 3 on Arduino Uno
// - To be connnected to INPUT PIN 2 on ULN2003 board
// - Which drives OUT PIN 2 on ULN2003 board
// - Which drives (-) on 5-way valve
//
int valve_5way = 3; //Red LED for debugging

//
// PIN 4 on Arduino Uno
// - To be connnected to INPUT PIN 3 on ULN2003 board
// - Which drives OUT PIN 3 on ULN2003 board
// - Which drives (-) on the FAN
//
int fan_control = 4; // Yellow LED for debugging


// Scale in which timing values are expressed (as multiplies of the number below)
int timing_unit_scale_milliseconds = 1000;

// Time for opening the 2-way valve
// 1 time units
//int timing_valve_2way = 2;

// Time for alternating the 5-way valve
// 8 time units
//int timing_valve_5way_alternating = 7;

void setup() {

  Serial.begin(9600); // open the serial port at 9600 bps

  //setup the display
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3D (for the 128x64) // init done // Show image buffer on the display hardware.
  display.setTextSize(1); //Size of the font
  display.setTextColor(WHITE); //colour
  display.setCursor(10, 0); //position of the cursor
  display.clearDisplay(); //stops the Adafruit logo from being shown
  display.display();
  display.println("Welcome"); // using display.println to display your output to lcd


  //initialize digital pin LED_BUILTIN as an output.
  pinMode(valve_2way, OUTPUT);
  pinMode(valve_5way, OUTPUT);
  pinMode(fan_control, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //make the fan work all the time for now
  //TBD - add temperature-control driven fan (based on the temperature of the copper loop)
  digitalWrite(fan_control, HIGH);
  display.clearDisplay();
  display.println("Fan on Yellow LED");
  Serial.print("Fan on yellow LED");
  //}

  //void halfCycle(int state_5way)
  //{
  //digitalWrite(LED_BUILTIN, state_5way);   // turn the built-in LED with the same value as 5-WAY state

  // Turn on 5-way
  //digitalWrite(valve_5way, state_5way);
  // Wait for 5-way to be opened for the given amount of time
  //delay(timing_valve_5way_alternating * timing_unit_scale_milliseconds);

  // Turn on the 2-way briefly
  //digitalWrite(valve_2way, HIGH);
  //delay(timing_valve_2way * timing_unit_scale_milliseconds);
  //digitalWrite(valve_2way, LOW);
}

void loop() {
  //halfCycle(HIGH);
  //halfCycle(LOW);

  //see ref 1 - 3 for explanations of the functions

  //This block is for the 5 way valve timer
  int TimeCtrl5way = analogRead(A0); //reads the potentiometer
  int ValveTime5way = map(TimeCtrl5way, 0, 1023, 0, 10); // converts the analogue pot signal which goes from 0 to 1023 bits (1024 bit total) to value of 0 - 100
  digitalWrite(valve_5way, HIGH); //turn on the valve
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.clearDisplay();
  display.println("5 way valve time RLED" + ValveTime5way); //this goes before the delay function to ensure the time is displayed, could be amended later to count down the time. Prints the time pot value as converted to the oled screen
  Serial.print("5 way valve time RLED" + ValveTime5way);
  delay(timing_unit_scale_milliseconds * ValveTime5way); // Delay the Arduino from processing the next step by Scale * mapped pot value
  digitalWrite(valve_5way, LOW); //switches of the valve
  display.println("5 way valve off RLED");
  Serial.print("5 way valve off RLED");

  //This block is for the 2 way valve timer the code has the same function as before, only values are different
  int TimeCtrl2way = analogRead(A1);
  int valveTime2way = map(TimeCtrl2way, 0, 1023, 0, 4);
  digitalWrite(valve_2way, HIGH); //turn on the valve
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10, 0);
  display.clearDisplay();
  display.println("2 way valve time GLED" + valveTime2way);
  Serial.print("2 way valve time GLED" + valveTime2way);
  delay(timing_unit_scale_milliseconds * valveTime2way);
  digitalWrite(valve_2way, LOW);
  display.println("2 way valve off GLED");
  Serial.print("2 way valve off GLED");

}

//References for the code:
//  1) Used for using a potentiometer to set the valve timing https://www.instructables.com/id/Arduino-101-Essentials-Reading-Analog-Input-Signal/
//  2) Map function for mapping the potentiometer https://www.arduino.cc/reference/en/language/functions/math/map/
//  3) Example code for map function https://www.arduino.cc/en/Tutorial/StepperSpeedControl
//  5) https://www.arduino.cc/en/Tutorial/StepperSpeedControl
