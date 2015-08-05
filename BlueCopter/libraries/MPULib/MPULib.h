/*
  Created by Basel Al-Rudainy, 6 april 2013.
  MODIFIED to use the MPU 6050 instead of the ADXL345 and L3G4200D.
  
  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.
*/
#ifndef MPULib_h
#define MPULib_h

#include "Arduino.h"
#include "Wire.h"

// <---------ADXL345->MPU6050-------------->
#define ADXL_addr 0x68  //addr-pin LOW //TODO, modify name so it's more relevant

#define ACCEL_CONFIG 0x1C // -- changing this value determines whether its +-2, 4, 8, or 16g. we want 16g.
#define PWR_MGMT_1 0x6B // put this in cycle mode
#define PWR_MGMT_2  0x6C // -- changing this value should delay the start of the activity function or auto sleep or put it in standby mode or measurement mode.  (that last bit is the most important) -- use this to determine the wake frequency
#define REG_BW_RATE	0x2C //TODO: -- changing the value inside will put in in a high or low power setting, and or select the device bandwidth and output data rate. ----- select the device bandwidth.

#define DATAX0  0x3C  //LSB
#define DATAX1  0x3B  //MSB
#define DATAY0  0x3E  //LSB
#define DATAY1  0x3D  //MSB
#define DATAZ0  0x40  //LSB
#define DATAZ1  0x41  //MSB
// <-------------------------------->

// <---------L3G4200D->MPU6050-------------->

#define L3G4_addr 0x68  //SDO-pin HIGH
// TODO
#define CTRL_REG1  0x20
#define CTRL_REG2	0x21
#define CTRL_REG4  0x23
#define CTRL_REG5 0x24
#define L3G4_HPF	0x13
#define L3G4_LPF	0x34
#define L3G4_BW_ENAX	0x8F
#define MODE_250  0x00
#define MODE_500  ((0x01)<<4) 
#define MODE_2000 ((0x03)<<4) 
#define SCALE_250  (8.75/1000.0)
#define SCALE_500  (17.5/1000.0)
#define SCALE_2000  (70.0/1000.0)
//--

#define READALLSIX  0x43 | (1 << 7)
#define OUT_X_L  0x44
#define OUT_X_H  0x43
#define OUT_Y_L  0x46
#define OUT_Y_H  0x45
#define OUT_Z_L  0x48
#define OUT_Z_H  0x47
// <-------------------------------->
/*
// <---------HMC5883-------------->
#define HMC_addr	0x1E
#define HMC_mode_reg	0x02
#define HMC_contm_val	0x00
#define HMC_X_MSB	0x03
// <-------------------------------->*/

class MPULib
{
public:
MPULib();
void init();
void getAxlData(int buff[]);
void getGyroData(float buff[]);
//void getMagData(int buff[]);
private:
void readCmd(byte addr,byte reg,byte num,byte buff[]);
void writeCmd(byte addr, byte reg, byte val);
};

#endif
