/*------------------------------------------------------------
This is the .cpp file for ARDUINO PEDOMETER Library
This is the property of Frugal Labs Tech Solutions Pvt. Ltd.
Please refer lisence.txt for complete details.
-------------------------------------------------------------*/
#include "Arduino.h"
#include "ArduinoPedometer.h"
#include "SoftwareSerial.h"
#include "ArduinoJson.h"

SoftwareSerial myflipSerial(RX, TX);

ArduinoPedometer::ArduinoPedometer()
{   
    myflipSerial.begin(9600);
    Serial.begin(9600);
    pinMode(13,OUTPUT);
}

int ArduinoPedometer::getPedo()
{
  int acc=0;
  float totvect[15]={0};
  float totave[15]={0};
  float xaccl[15]={0};
  float yaccl[15]={0};
  float zaccl[15]={0};
  for (int i=0;i<15;i++)
  {
    xaccl[i]=float(analogRead(xpin));
    delay(1);
    yaccl[i]=float(analogRead(ypin));
    delay(1);
    zaccl[i]=float(analogRead(zpin));
    delay(1);
    totvect[i] = sqrt(((xaccl[i]-xavg)* (xaccl[i]-xavg))+ ((yaccl[i] - yavg)*(yaccl[i] - yavg)) + ((zval[i] - zavg)*(zval[i] - zavg)));
    totave[i] = (totvect[i] + totvect[i-1]) / 2 ;
    delay(150);

    //cal steps 
    if (totave[i]>threshhold && flag==0)
    {
       steps=steps+1;
       flag=1;
    }
    else if (totave[i] > threshhold && flag==1)
    {
        //do nothing 
    }
    if (totave[i] <threshhold  && flag==1)
    {
      flag=0;
    }
   // Serial.print("steps=");
   // Serial.println(steps);
   return(steps);
  }
  delay(100);
}

void ArduinoPedometer::calibrate()
{
  digitalWrite(13,HIGH);
  Serial.println("Calibrating......");
  float sum=0;
  float sum1=0;
  float sum2=0;
  for (int i=0;i<15;i++)
  {
    xval[i]=float(analogRead(xpin));
    sum=xval[i]+sum;
  }
  delay(15);
  xavg=sum/15.0;
  Serial.println(xavg);
  for (int j=0;j<15;j++)
  {
    xval[j]=float(analogRead(xpin));
    sum1=xval[j]+sum1;
  }
  yavg=sum1/15.0;
  Serial.println(yavg);
  delay(15);
  for (int i=0;i<15;i++)
  {
    zval[i]=float(analogRead(zpin));
    sum2=zval[i]+sum2;
  }
  zavg=sum2/15.0;
  delay(15);
  Serial.println(zavg);
  digitalWrite(13,LOW);
  Serial.println("Calibration Successful!");
  //delay(1500);
}

void ArduinoPedometer::printPedo(int p)
{
  myflipSerial.begin(9600);
  Serial.print("Steps: ");
  Serial.println(p);
  myflipSerial.print("Steps: ");
  myflipSerial.println(p);
  delay(100);
}

void ArduinoPedometer::jsonPrint(int pdo)
{
  myflipSerial.begin(9600);
  StaticJsonBuffer<300> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["Steps"] = pdo;
  root.printTo(myflipSerial);
  myflipSerial.println();
  delay(500);
}
