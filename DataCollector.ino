//Author: Paramveer Singh
//Created on: 7 March 2022
//Description: This program simply polls the EC and RTD sensors 10 times
//             and puts the readings into a 10 element float buffer for each sensor.

#include <Ezo_i2c.h>  //include the EZO I2C library from https://github.com/Atlas-Scientific/Ezo_I2c_lib
#include <Wire.h>     //include library for activating Arduino's I2C.
#include <sequencer2.h> //imports a 2 function sequencer

Ezo_board EC = Ezo_board(100, "EC");
Ezo_board RTD = Ezo_board(102, "RTD");

float EC_data[10];
float RTD_data[10];
int elementNum;

void step1();
void step2();

Sequencer2 Seq(&step1, 1000,
               &step2, 0);

void setup() {
  Serial.begin(9600); //Start serial port
  Wire.begin(); //start i2c
  Seq.reset();  //initialize sequencer
  delay(10000);
  
  for(elementNum = 0; elementNum < 10; ++elementNum)
  {
    Seq.run();
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

void step1()
{
  RTD.send_read_cmd();
  EC.send_read_cmd();
}

void step2()
{
  if(RTD.get_error() == Ezo_board::SUCCESS && RTD.get_last_received_reading() > -1000.0)    //Check if the data is valid or not
  {
     RTD_data[elementNum] = RTD.get_last_received_reading();
  }
  else
  {
    RTD_data[elementNum] = 25.0f;
  }

  EC_data[elementNum] = EC.get_last_received_reading();
}
