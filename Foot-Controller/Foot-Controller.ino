#include "MPU9250.h"
#include <SoftwareSerial.h>
#include <math.h>

MPU9250 mpu;

//this is a github version
/*
 * ToDo:
 * -upload gravity calibration.ino DONE
 * -calibrate gravity and test other functions DONE
 * -disable startup comment in mpu.update() DONE
 * -move the library to the github DONE
 * -change the angles to 0 - 360
 * -linAcc and appAcc have the same definition, remove the one that is not used
 * 
 * I should use velocity or distance instead of acceleration
 */

float maximum[3];

int packet; //number of data
int start_time = 0;
float data_rate = 0;

SoftwareSerial hid(3, 2);

void setup()
{
  Serial.begin(57600);
  Wire.begin();

  mpu.setup();
  mpu.setGravity(0.955);

  hid.begin(57600);
  hid.write("@@@"); // activate the command mode
 
  delay(2000); //ignore first few values
}

void loop()
{
  static uint32_t prev_ms = millis();
    
  if ((millis() - prev_ms) > 1) // millis() > 4200 does  not ignore the first values. Perhaps the value changes as I read it
  {
    mpu.update();

    if (Serial.available())
    {
      //mpu.setGravity(Serial.parseFloat());
    }

    if (millis() > 4200)
    {
      //record maximum
      for (int i = 0; i < 3; i ++)
      {
        if (maximum[i] < mpu.getAppAcc(i))
        {
          maximum[i] = mpu.getAppAcc(i);
        }
      }

      // measuring the data rate
      // unit: data per second
      if (start_time == 0)
      {
        start_time = millis();
      }
      
      packet ++;
      data_rate = (float)packet / (millis() - start_time);
    }
       
    Serial.print(mpu.getRoll(), 2);
    Serial.print(" ");
    Serial.print(mpu.getPitch(), 2);
    Serial.print(" ");
    Serial.print(mpu.getYaw(), 2);
    Serial.print("      ");
        
    for(int i = 0; i < 3; i ++)
    {
      Serial.print(mpu.getAcc(i), 2);
      Serial.print(" ");
    }
    
    Serial.print("      ");

    for(int i = 0; i < 3; i ++)
    {
      Serial.print(mpu.getAppAcc(i), 2);
      Serial.print(" ");
    }

    Serial.print("      ");

    for(int i = 0; i < 3; i ++)
    {
      Serial.print(maximum[i], 2);
      Serial.print(" ");
    }

    Serial.print("      ");
    Serial.print(mpu.getGravity(), 3);
    Serial.print("      ");
    Serial.print(mpu.getCalculatedGravity(), 3);
    Serial.print("      ");
    Serial.print(millis());
    Serial.print("    ");
        
    int x = round(mpu.getAppAcc(1) * 100 + 1);
    int y = round(mpu.getAppAcc(0) * 100 + 1);

    //come up with a way to define deadzone
    if (abs(x) < 5)
    {
      x = 0;
    }

    if (abs(y) < 5)
    {
      y = 0;  
    }
        
    Serial.print(x);
    Serial.print("    ");
    Serial.print(y);
    Serial.print("    ");
    Serial.print(data_rate * 1000);
    Serial.print("    ");
    Serial.print(packet);
    Serial.print("    ");
    Serial.print(start_time);
    Serial.println("");

    sendMouseReport(0, x, y, 0); //move this so that it only works approximately after 4s

    prev_ms = millis();
  }
}

void sendMouseReport (int stat, int dx, int dy, int dz)
{
  byte mouseReport[] = {(byte)stat, (byte)dx, (byte)dy, (byte)dz};
  hid.write("M");
  hid.write(mouseReport, 4);
  hid.write("\r\n");
}
