//-----------------------------------------------------------------------------------
//  TinyCircuits SRAM Example Sketch
//  Last Updated 23 February 2018
//
//  This sketch writes a string of text to a specifice memory address, reads the
//  text back from memory, then prints the text to demonstrates some functions of
//  the TinyCircuits SRAM Tinyshield, which uses the Microchip 23LC1024 SRAM
//  memory module.
//
//  Library written by ennui2342 on github https://github.com/ennui2342/arduino-sram
//
//  Example Written by Nick DiVitto for TinyCircuits http://Tinycircuits.com
//
//-----------------------------------------------------------------------------------

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
  sram.seek(1);
  sram.write((byte *) test, sizeof(test));
  char buf[20];
  sram.seek(1);
  sram.readBytes((char *) buf, sizeof(buf));
  SerialMonitorInterface.println(buf);
  delay(500);
}


