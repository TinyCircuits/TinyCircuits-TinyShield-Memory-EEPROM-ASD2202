/*
  TinyCircuits SRAM Example Sketch
  
  This sketch writes a string of text to a specifice memory address, reads the
  text back from memory, then prints the text to demonstrates some functions of
  the TinyCircuits SRAM Tinyshield, which uses the Microchip 23LC1024 SRAM
  memory module.

  Library written by ennui2342 on github https://github.com/ennui2342/arduino-sram

  Written 02 July 2018
  By Nick DiVitto
  Modified 09 January 2019
  By Hunter Hykes

  https://TinyCircuits.com
*/

#include <SRAM.h>
#include <SPI.h>
#define SRAM_CS_PIN 5

#if defined (ARDUINO_ARCH_AVR)
#define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
#define SerialMonitorInterface SerialUSB
#endif

SRAM sram(SRAM_CS_PIN, SRAM_1024);

void setup() {
  SerialMonitorInterface.begin(9600);
  //  while (!SerialMonitorInterface); //This line will block until a serial monitor is opened with TinyScreen+!
  SPI.begin();
  SerialMonitorInterface.println("SRAM Test");
  sram.begin();
}

void loop() {
  char test [] = "hello, world";
  sram.seek(1); //Goes to address '1' within SRAM
  sram.write((byte *) test, sizeof(test)); //writes the contents of test to SRAM at the previously specified address
  char buf[20];
  sram.seek(1); //Goes to address '1' within SRAM
  sram.readBytes((char *) buf, sizeof(buf)); //reads the contents of SRAM at the previously specified address to buf
  SerialMonitorInterface.println(buf);
  delay(500);
}
