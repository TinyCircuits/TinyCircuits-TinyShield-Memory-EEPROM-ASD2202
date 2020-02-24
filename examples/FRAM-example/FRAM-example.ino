/**********************************************************************
 * FRAM Memory TinyShield Example:
 * Performs a basic write and read operation of a string to FRAM chip
 * 
 * Written by: Laveréna Wienclaw for TinyCircuits
 * Initialized: Feb 2020
 * Last modified: 
 *********************************************************************/

#include <FRAM.h>

// Make Serial Monitor compatible for all TinyCircuits processors
#if defined(ARDUINO_ARCH_AVR)
  #define SerialMonitorInterface Serial
#elif defined(ARDUINO_ARCH_SAMD)
  #define SerialMonitorInterface SerialUSB
#endif

uint8_t FRAM_CS_PIN = 5;
FRAM fram(FRAM_CS_PIN);

void setup() {
  SerialMonitorInterface.begin(9600);
  fram.begin();
}

void loop() {
  char test [] = "hello, world";
  fram.seek(1);
  SerialMonitorInterface.print("Data to write: ");
  SerialMonitorInterface.println(test);
  fram.write((byte *) test, sizeof test);
  char buf[100];
  fram.seek(1);
  fram.readBytes((char *) buf, sizeof buf);
  SerialMonitorInterface.print("Data read: ");
  SerialMonitorInterface.println(buf);
  delay(1000);

//  int framData = fram.read();
//  SerialMonitorInterface.println(framData);
}
