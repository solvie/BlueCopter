/*
  Created by Basel Al-Rudainy, 6 april 2013.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/

#include "MPULib.h"
#include "Arduino.h"
#include "Wire.h"

MPULib::MPULib()
{

}

void MPULib::init(){
Wire.begin(); 
//init - Accel part
writeCmd(MPU_addr,ACCEL_CONFIG,0x18); //+-16g SET THE G RANGE
writeCmd(MPU_addr,PWR_MGMT_1, 0x2B);  //choose cycle mode + clock
writeCmd(MPU_addr,PWR_MGMT_2, 0xC0); // wake up frequency 20hz
writeCmd(MPU_addr,CONFIG, 0x04); //bandwidth 21hz delay 8.5hz chosen
//-----end init Accel

//init - Gyro part

writeCmd(MPU_addr,CTRL_REG4, 0xF8); //set to 2000dps

//-----end init Gyro

// we don't have a magnetoscope
// writeCmd(HMC_addr,HMC_mode_reg,HMC_contm_val);
//
}

void MPULib::getAxlData(int buff[]){
byte buffer[6];
readCmd(ADXL_addr,DATAX0,6,buffer);
buff[0]=(buffer[1]<<8) | buffer[0];
buff[1]=(buffer[3]<<8) | buffer[2];
buff[2]=(buffer[5]<<8) | buffer[4];

}

void MPULib::getGyroData(float buff[]){
byte buffer[6];
readCmd(L3G4_addr,READALLSIX,6,buffer);
buff[0]=(float)((int)(buffer[1]<<8) | buffer[0])*SCALE_2000;
buff[1]=(float)((int)(buffer[3]<<8) | buffer[2])*SCALE_2000;
buff[2]=(float)((int)(buffer[5]<<8) | buffer[4])*SCALE_2000;
}
/*
void MPULib::getMagData(int buff[]){
byte buffer[6];
readCmd(HMC_addr,HMC_X_MSB,6,buffer);
buff[0]=(buffer[0]<<8) | buffer[1];
buff[2]=(buffer[2]<<8) | buffer[3];
buff[1]=(buffer[4]<<8) | buffer[5];
}*/

void MPULib::readCmd(byte addr,byte reg,byte num,byte buff[]){
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom(addr, num);
  while(Wire.available()<num);
  for(byte i = 0;i<num;i++){
  buff[i] = Wire.read();
  }
}

void MPULib::writeCmd(byte addr, byte reg, byte val){
  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);
  Wire.endTransmission();
}
