/************* Arduino Pedometer with HC-05 ******************
  This project collects data from the ADXL-335 accelerometer.
  Arduino processes it and calculates the "No. of Steps" taken
  from the time of power up. the data is encoded in Json string format
  and sent serially using a BT module HC-05.
  ---------------------------------------------------------------------
  created on 16 Dec 2015
  by Abhay Shankar Bharadwaj
  (abhaysbharadwaj@gmail.com)
  (facebook.com/abhaysbharadwaja)
  ---------------------------------------------------------------------
  credits go to Benoit Blanchon for the ArduinoJson library
  and jatinbatra (http://www.instructables.com/member/jatinbatra/)
  who created the original pedometer code.
  ---------------------------------------------------------------------
  This project code is in the public domain.
  It is given as is, and any modifications can be done
  as an open sorce standard. credits to be updated wherever
  and whenever necessary.
  ---------------------------------------------------------------------
  ----------------------- connection details --------------------------
  ADXL335 accelerometer & Arduino nano:
  Vcc --> +5v
  X --> A5
  Y --> A6
  Z --> A7
  Gnd --> gnd
  BT HC05 Tx to software Rx (D11)
  BT HC05 Rx to software Tx (D10)
  you can change the pind in .h file
  ----------------------------------------------------------------------
  you must include the "ArduinoJson" and "SoftwareSerial"
  libraries in arduino's library directory
  (C:\Program Files (x86)\Arduino\libraries)
  (or ...\Arduino\libraries)
  you can download the libraries from:
  ArduinoJson: https://github.com/bblanchon/ArduinoJson
  SoftwareSerial: https://github.com/arduino/Arduino/tree/master/hardware/arduino/avr/libraries/SoftwareSerial
**********************************************************/
 
#include "ArduinoPedometer.h"

ArduinoPedometer fp; //create an instacne called "fp" for the class "ArduinoPedometer"
int x;

void setup()
{
  fp.calibrate(); // perform calibration to get x,y,z parameters.
  delay(1000);
}

void loop()
{
  x = fp.getPedo(); //get the no. of steps
  fp.jsonPrint(x); //print the value in json format in software serial.
  delay(200);
}
