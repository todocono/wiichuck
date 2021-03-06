/*
 * WiiChuck -- working demo
 *
 * Animatronics - NYU Shanghai
 * Prof. Rodolfo Cossovich
 *
 * Original code from Tod E. Kurt, http://thingm.com/
 * Code works for both original WII Nunchuck and OEM joysticks
 *
 */

#include <Wire.h>
#include "nunchuck_funcs.h"

int loop_cnt = 0;

byte accX, accY, accZ, joyX, joyY, joyZ, butZ, butC;

void setup()
{
  delay (1000);
  Serial.begin(9600);
  nunchuck_setpowerpins();
  nunchuck_init(); // send the initilization handshake
  Serial.print("WiiChuck ready to transmit ... \n");
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
}

