//Author: Paramveer Singh
//Created on: 7 March 2022
//Updated on: 17 May 2022
//Description: This program simply polls the EC and RTD sensors 10 times
//             and puts the readings into a 10 element float buffer for each sensor.

#include <Ezo_i2c.h>  //include the EZO I2C library from https://github.com/Atlas-Scientific/Ezo_I2c_lib
#include <Wire.h>     //include library for activating Arduino's I2C.
#include <Ezo_i2c_util.h> //brings in common print statments

Ezo_board EC = Ezo_board(100, "EC");
Ezo_board RTD = Ezo_board(102, "RTD");

float EC_data[10];
float RTD_data[10];
int elementNum;

void SendReadCmds();
void ReadReadings();


void setup() {
  Serial.begin(9600); //Start serial port
  Wire.begin(); //start i2c
  delay(3000);
  for(elementNum = 0; elementNum < 10; elementNum++)
  {
    SendReadCmds();
    delay(1000);
    ReadReadings();
    delay(100);
  }

  Serial.println("10 data points received");
  Serial.print("RTD: ");
  for(int i = 0; i < 10; ++i)
  {
    String stringToPrint = String(RTD_data[i], 3);
    Serial.print(stringToPrint + " ");
  }
  Serial.print("\n");
  Serial.print("EC: ");
  for(int i = 0; i < 10; ++i)
  {
    String stringToPrint = String(EC_data[i], 3);
    Serial.print(stringToPrint + " ");
  }
  Serial.print("\n");
  
}

void loop() {
}

void SendReadCmds()
{
  RTD.send_read_cmd();
  EC.send_read_cmd();
}

void ReadReadings()
{
  RTD.receive_read_cmd();
  if(RTD.get_error() == Ezo_board::SUCCESS)    //Check if the data is valid or not
  {
    float reading = RTD.get_last_received_reading();
    RTD_data[elementNum] = reading;
  }
  else
  {
    RTD_data[elementNum] = 25.0f;
  }
  EC.receive_read_cmd();
  EC_data[elementNum] = EC.get_last_received_reading();
}
