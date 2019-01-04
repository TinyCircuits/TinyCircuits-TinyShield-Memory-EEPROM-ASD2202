//-------------------------------------------------------------------------------
//  TinyCircuits EEPROM TinyShield Example Sketch
//  Last Updated 3 May 2016
//  
//  This is an example of how to write and read bytes to the 24FC1025 I2C EEPROM
//  using the Wire library. Page write transactions are not used. The address
//  resistors on the board are both low (0) by default.
//
//  Written by Ben Rose for TinyCircuits, https://tinycircuits.com
//
//-------------------------------------------------------------------------------

#include <Wire.h>

#define EEPROM_A0 0
#define EEPROM_A1 0
#define EEPROM_ADDR 0x50|(EEPROM_A1<<1)|(EEPROM_A0<<0)

void setup() {
  Wire.begin();
  Serial.begin(115200);
  Serial.println("Writing..");
  char writeData[]="TinyCircuits!";
  EEPROMwrite(0,(uint8_t*)writeData,sizeof(writeData));
  char readData[]="If you see this, there's an error!";
  Serial.println("Reading..");
  EEPROMread(0,(uint8_t*)readData,sizeof(writeData));
  Serial.println(readData);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void EEPROMread(unsigned long addr, uint8_t* buff, unsigned long count){
  for(unsigned long i=0;i<count;i++){
    buff[i]=EEPROMread(addr+i);
  }
}

void EEPROMwrite(unsigned long addr, uint8_t* buff, unsigned long count){
  for(unsigned long i=0;i<count;i++){
    EEPROMwrite(addr+i,buff[i]);
  }
}

byte EEPROMread(unsigned long addr){
  uint8_t val=255;
  uint8_t I2Caddr=EEPROM_ADDR;
  if(addr>0x0000FFFF){
    I2Caddr|=0x04;
  }
  Wire.beginTransmission(I2Caddr);
  Wire.write(addr>>8);
  Wire.write(addr);
  Wire.endTransmission();
  Wire.requestFrom(I2Caddr,(uint8_t)1);
  while(Wire.available()){
    val=Wire.read();
  }
  return val;
}

byte EEPROMwrite(unsigned long addr, byte val){
  uint8_t I2Caddr=EEPROM_ADDR;
  if(addr>0x0000FFFF){
    I2Caddr|=0x04;
  }
  Wire.beginTransmission(I2Caddr);
  Wire.write(addr>>8);
  Wire.write(addr);
  Wire.write(val);
  Wire.endTransmission();
  Wire.beginTransmission(I2Caddr);
  unsigned long timeout=millis();
  while(Wire.endTransmission() && millis()-timeout<10){
    Wire.beginTransmission(I2Caddr);
  }
}
