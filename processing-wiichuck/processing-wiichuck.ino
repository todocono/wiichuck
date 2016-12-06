/*
   deltabot_Arduino.ino
   Latest version  0.3 by Rudi Cossovich
   Last edit: 21 November 2016
   This is a modified version of:
   http://ima.nyu.sh/animatronics/

   deltabot_servos.pde
   Created by  Matt Greensmith, 25 May 2011
    (https://mattgreensmith.wordpress.com/2011/11/26/making-an-arduino-controlled-delta-robot/)
   Based on:
   MultipleSerialServoControl.pde
   Created:  23 December 2009
   Author:   Brian D. Wendt
    (http://principialabs.com/)
   Version:  1.1
   License:  GPLv3
    (http://www.fsf.org/licensing/)

*/

#include <Wire.h>
#include "nunchuck_funcs.h"

// Import the Arduino Servo library
#include <Servo.h>

// Physical pins where servos will be attached.
int SERVO_1_PIN = 6;
int SERVO_2_PIN = 7;
int SERVO_3_PIN = 8;
int SERVO_4_PIN = 9;
int SERVO_5_PIN = 10;
int SERVO_6_PIN = 11;

// Create a Servo object for each servo
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

// Common servo setup values
int minPulse = 600;   // minimum servo position, us (microseconds)
int maxPulse = 2400;  // maximum servo position, us
boolean servosEnabled = false;  //servo power enabled

// User input for servo and position
int userInput[3];    // raw input from serial buffer, 3 bytes
int startbyte;       // start byte, begin reading input
int servo;           // which servo to pulse?
int pos;             // servo angle 0-180
int i;               // iterator

// LED on Pin 13 to indicate if servos have power
int ledPin = 13;
int ledPinState = LOW;


int pos1 = 0;    // variable to store the servo position
int pos2 = 0;    // variable to store the servo position
int pos3 = 0;

int loop_cnt = 0;

byte accX, accY, accZ, joyX, joyY, joyZ, butZ, butC;

void setup()
{
  pinMode(ledPin, OUTPUT);

  // Open the serial connection, 9600 baud
  Serial.begin(9600);

  delay (1000);
  // Serial.begin(9600);
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake
  Serial.print("WiiChuck ready to transmit ... \n");

  servo1.attach(11);  // attaches the servo on pin 9 to the servo object ---ARM
  servo2.attach(10);  // attaches the servo on pin 10 to the servo object ---EYES
  servo3.attach(9); // --- HAND
  servo4.attach(8); // --- processing controlled
  servo5.attach(7); // --- processing controlled
  servo6.attach(6); // --- processing controlled


}

void loop()
{
  // Wait for serial input (min 3 bytes in buffer)
  if (Serial.available() > 2) {
    // Read the first byte
    startbyte = Serial.read();
    // If it's really the startbyte (255) ...
    if (startbyte == 255) {
      // ... then get the next two bytes
      for (i = 0; i < 2; i++) {
        userInput[i] = Serial.read();
      }
      // First byte = servo to move?
      servo = userInput[0];
      // Second byte = which position?
      pos = userInput[1];
      // Packet error checking and recovery
      if (pos == 255) {
        servo = 255;
      }

      // Assign new position to appropriate servo
      switch (servo) {
        case 1:
          servo4.write(pos);    // move servo1 to 'pos'
          break;
        case 2:
          servo5.write(pos);
          break;
        case 3:
          servo6.write(pos);
          break;


        // Enable or disable servos, display status on LED
        case 99:
          if (pos == 180) {  //enable
            if ( !servosEnabled ) {

              attachServos();
            }
            ledPinState = HIGH;
          }
          if (pos == 0) {    //disable

            detachServos();
            ledPinState = LOW;
          }
          digitalWrite(ledPin, ledPinState);
          break;
      }
    }
  }

  if ( loop_cnt > 100 ) { // every 100 msecs get new data
    loop_cnt = 0;

    nunchuck_get_data();

    joyX  = nunchuck_joyx(); // ranges from approx 70 - 182
    joyY  = nunchuck_joyy(); // ranges from approx 65 - 173


    accX  = nunchuck_accelx(); // ranges from approx 70 - 182
    accY  = nunchuck_accely(); // ranges from approx 65 - 173
    accZ  = nunchuck_accelz(); // ranges from approx 65 - 173

    butZ = nunchuck_zbutton();
    butC = nunchuck_cbutton();

    Serial.print("joyX: "); Serial.print((byte)joyX, DEC);
    Serial.print("  joyY: "); Serial.print((byte)joyY, DEC);

    Serial.print("  accX: "); Serial.print((byte)accX, DEC);
    Serial.print("  accY: "); Serial.print((byte)accY, DEC);
    Serial.print("  accZ: "); Serial.print((byte)accZ, DEC);

    Serial.print("  butZ: "); Serial.print((byte)butZ, DEC);
    Serial.print("  butC: "); Serial.println((byte)butC, DEC);
  }
  loop_cnt++;
  delay(1);

  //here we calculate where servos will move to
  pos1 = map ( accY, 1, 255, 0, 180);       //check map() syntax at https://www.arduino.cc/en/Reference/Map
  pos2 = map ( joyX, 1, 255, 0, 180);
  pos3 = map (joyY, 1, 255, 0, 180);

  //here we update servos positions. Check
  servo1.write(pos1);              // tell servo to go to position in variable 'pos'
  servo2.write(pos2);              // tell servo to go to position in variable 'pos'
  servo3.write(pos3);
}

void attachServos() {
  // Attach each Servo object to a digital pin
  servo4.attach(SERVO_1_PIN, minPulse, maxPulse);
  servo5.attach(SERVO_2_PIN, minPulse, maxPulse);
  servo6.attach(SERVO_3_PIN, minPulse, maxPulse);
  servosEnabled = true;
}

void detachServos() {
  servo4.detach();
  servo5.detach();
  servo6.detach();
  servosEnabled = false;
}



