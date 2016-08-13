/**
 * This code is to control the exercise bike add-on built by Paly Robotics. 
 * 
 * Device: Arduino Uno Rev3
 * 
 * @author Jonathan Zwiebel, Prashanti Anderson
 * @version 12 August 2016
 */

#include <Servo.h>

int const HFX_PIN = 2; // Read pin for the U1881 hall effect sensor
int const SERVO_PIN = 9 // Write pin for the HS-322HD servo motor

// Object for servo motor
Servo servo;

// Time signature of previous tick polling (ms)
long last_time_check;

// Tick accumulator to store ticks since last time check 
int tick_acc;

// Run on program initialization
void setup() {
  // Intializes the input and output pins
  servo.attach(SERVO_PIN);
  pinMode(HFX_PIN, INPUT_PULLUP);

  // Sets the hall effect pin to call onRise when transfering from LOW to HIGH state
  attachInterrupt(digitalPinToInterrupt(HFX_PIN), onRise, RISING);

  // Creates a serial transfer with baud rate 9600
  Serial.begin(9600);

  // Sets the initial last_time_check value
  last_time_check = millis();
}

// Executed on loop
void loop() {  
  // If time delta is greater than 2.5 s adjust servo position
  if(millis() - last_time_check >= 2500) {
    // Calculate and set servo
    float scaledPos = (float) tick_acc / 30;
    if(scaledPos > 1) {
      scaledPos = 1;
    }
    float servoPos = 270 * (1 - scaledPos);
    servo.write(servoPos);

    // Printed output
    Serial.print("Counted Ticks: ");
    Serial.println(tick_acc);

    // Reset loop
    tick_acc = 0;
    last_time_check = millis();
  }
}

// Called when hall effect pin state switches from LOW to HIGH
// Increases the tick accumulator
void onRise() {
  tick_acc++;
}
