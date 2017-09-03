/**
 * This code is to control the exercise bike add-on built by Paly Robotics. 
 * 
 * Device: Arduino Uno Rev3
 * 
 * @author Jonathan Zwiebel, Eli Zucker
 * @version 3 September 2017
 */

#include <Wire.h>

int a_pot_pin = A0;
int b_pot_pin = A1;
int hfx_pin = 2;
int inc = 0;
int up_count = 0;
int down_acc = 1;
int prev_inc = 0;
int current_volume = 0;

// Run on program initialization
void setup() {
  Wire.begin();
  initializeTPA6130();
  Serial.begin(9600);
  pinMode(hfx_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(hfx_pin), onRise, RISING);
}

// Executed on loop
void loop() {  
  //double a_value = analogRead(a_pot_pin);
  //Serial.print("A: ");
  //Serial.println(a_value);
  //int target_volume = (int) ((1020 - a_value) * 63 / 1020);
  //Serial.print("Volume: " );
  //Serial.println(target_volume);
  delay(10);
  up_count++;
  if(up_count == 50){
    Serial.println("Count reset to 0");
    up_count = 0;
    if(inc > 0){
      if(prev_inc == inc && down_acc < 5) {
        down_acc++;
      }
      else {
        down_acc = 1;
      }

      double drop_multiplier = inc / 5.0;
      
      inc -= (int) (down_acc * drop_multiplier);
      if(inc < 0) {
        inc = 0;
      }
      Serial.print("Inc decreased to: ");
      Serial.println(inc);
    }
    prev_inc = inc;
  }
  int target_volume = 2 * inc;
  if(target_volume > 63) {
    target_volume = 63;
  }
  setVolume(target_volume);
}

// Initialize the TPA6130 chip
void initializeTPA6130() {
  Wire.beginTransmission(0x60);
  Wire.write(1);
  Wire.write(0xC0);
  Wire.write(0x00);
  Wire.endTransmission();
}

// Change the volume on the TPA6130 chip
// Volume is an integer in the range 0-63 in increments of ~1 dB
void setVolume(int volume) {
  Wire.beginTransmission(0x60);
  Wire.write(2);
  Wire.write(volume);
  Wire.write(0x00);
  Wire.endTransmission();
}

// Mute the headphones
void mute() {
  Wire.beginTransmission(0x60);
  Wire.write(2);
  Wire.write(0xC0);
  Wire.write(0x00);
  Wire.endTransmission();
}

void onRise() {
  inc++;
  Serial.print("Inc increased to: ");
  Serial.println(inc);
}

