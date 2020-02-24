#include <SPI.h>
#include "FRAM.h"

FRAM::FRAM(uint8_t pin) {
  cs_pin = pin;
}

void FRAM::begin() {
  SPI.begin();
  pinMode(cs_pin, OUTPUT);
  digitalWrite(cs_pin, HIGH);
  address = 0;
}

void FRAM::seek(uint32_t addr) {
  address = addr;
}

size_t FRAM::write(uint8_t data) {
  digitalWrite(cs_pin, LOW);
  SPI.transfer(FRAM_WREN);
  digitalWrite(cs_pin, HIGH);

  digitalWrite(cs_pin, LOW);  
  SPI.transfer(FRAM_WRITE);
  SPI.transfer((uint32_t)(address >> 16) & 0xFF);
  SPI.transfer((uint32_t)(address >> 8)  & 0xFF);
  SPI.transfer((uint32_t)(address >> 0)  & 0xFF);
  SPI.transfer(data);
  address++;
  digitalWrite(cs_pin, HIGH);

  return 1;
}

int FRAM::read() {
  digitalWrite(cs_pin, LOW);
  SPI.transfer(FRAM_READ);
  SPI.transfer((uint32_t)(address >> 16) & 0xFF);
  SPI.transfer((uint32_t)(address >> 8)  & 0xFF);
  SPI.transfer((uint32_t)(address >> 0)  & 0xFF);
  uint8_t data = SPI.transfer(0);
  address++;
  digitalWrite(cs_pin, HIGH);
  
  return data;
}
