/*
   WiiChuck -- moving 2 servos with the joystick

   Animatronics - NYU Shanghai
   Prof. Rodolfo Cossovich

   Original code from Tod E. Kurt, http://thingm.com/
   Code works for both original WII Nunchuck and OEM joysticks

*/

#include <Wire.h>
#include "nunchuck_funcs.h"

#include <Servo.h>

Servo servo1, servo2, servo3, servo4, servo5, servo6, servo7, servo8, servo9, servo10, servo11, servo12;  // create servo object to control a servo

int pos1, pos2, pos3, pos4, pos5, pos6, pos7, pos8, pos9, pos10, pos11, pos12 = 0;    // variable to store the servo position

int loop_cnt = 0;

byte accX, accY, accZ, joyX, joyY, joyZ, butZ, butC;

void setup()
{
  delay (1000);
  Serial.begin(9600);
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake
  Serial.print("WiiChuck ready to transmit ... \n");
  servo1.attach(2);
  servo2.attach(3);
  servo3.attach(4);
  servo4.attach(5);
  servo5.attach(6);
  servo6.attach(7);
   servo7.attach(8);
    servo8.attach(9);
    servo9.attach(10);
    servo10.attach(11);
    servo11.attach(12);
    servo12.attach(13);
  

}

void loop()
{
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
  pos1 = map ( joyX, 50, 220, 0, 180);     //left mostache
  pos2 = map ( joyX, 220, 50, 0, 180);    //right mostache
  pos3 = butZ ? 30 : 70;                  //mouth
  pos4 = butC ? 30 : 150;                 //left eyelid
  pos5 = butC ? 150 : 30;                 //right eyelid
  pos6 = map ( accX, 40, 220, 0, 180);
  pos7 = map ( accX, 220, 40, 0, 180);
  pos8 = map ( accX, 40, 220, 0, 180);
  pos9 = map ( accX, 40, 220, 0, 180);
  pos10 = map ( accY, 40, 220, 0, 180);
  pos11 = map ( accY, 40, 220, 0, 180);
  pos12 = map ( accY, 40, 220, 0, 180);



  //here we update servos positions.

  servo1.write(pos1);              // tell servo to go to position in variable 'pos'
  servo2.write(pos2);              // tell servo to go to position in variable 'pos'
  servo3.write(pos3);              // tell servo to go to position in variable 'pos'
  servo4.write(pos4);              // tell servo to go to position in variable 'pos'
  servo5.write(pos5);              // tell servo to go to position in variable 'pos'
  servo6.write(pos6);              // tell servo to go to position in variable 'pos'
  servo7.write(pos7);              // tell servo to go to position in variable 'pos'
  servo8.write(pos8);              // tell servo to go to position in variable 'pos'
  servo9.write(pos9);              // tell servo to go to position in variable 'pos'
  servo10.write(pos10);              // tell servo to go to position in variable 'pos'
  servo11.write(pos11);              // tell servo to go to position in variable 'pos'
  servo12.write(pos12);              // tell servo to go to position in variable 'pos'

}

