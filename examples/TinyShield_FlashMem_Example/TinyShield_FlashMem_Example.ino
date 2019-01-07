/*
  TinyCircuits Flash Memory TinyShield Example Sketch
  
  This is an example of how to write to and read data from the Winbond W25Q80DV
  I2C Flash Memory using the SPIFlash library. Whole page write functions are
  not used. This example will specifically be using the writeByte/readByte
  functions. Documentation on functions for other data types can be found on
  the library's Github page.

  SPIFlash is authored by Marzogh: https://github.com/Marzogh/SPIFlash

  Written 19 January 2017
  By Lilith Freed
  Modified 07 January 2019
  By Hunter Hykes

  https://TinyCircuits.com
*/

#include <SPIFlash.h>

// Decide what Serial port to use!
#ifdef ARDUINO_ARCH_SAMD
  #define SerialMonitor SerialUSB // Our TinyScreen+ is an SAMD board.
#else
  #define SerialMonitor Serial
#endif

const int flashCS = 5; // The chip/slave select pin is pin 5.

SPIFlash flash(flashCS); // The SPIFlash object for the chip. Passed the chip select pin in the constructor.
uint16_t page; // The page to be written to. (Page value MUST be type uint16_t)
uint8_t offset; // The specific location on the page. (Offset value MUST be type uint8_t)

void setup() {
  SerialMonitor.begin(115200);
  while(!SerialMonitor); // This will ensure the serial monitor is OPEN before writing to it on TinyScreen+.
  
  SerialMonitor.println("Initializing Flash Memory...");
  SerialMonitor.println();
  pinMode(flashCS, OUTPUT); // Ensure chip select pin is an output. This line is currently REQUIRED for proper operation.
  flash.begin(); // Boots the flash memory
  SerialMonitor.println(); 

  page = random(0, 4095); // The W25Q80DV has 4,096 writeable pages, referenced as 0-4095 in this library.
  offset = random(0, 255); // There are 256 individually addressable bytes per page, referenced 0-255.

  /* Writing/Reading a byte */
  SerialMonitor.println("Using writeByte...");
  uint8_t testByte = 8;
  // writeByte(page, offset, byte) - returns true if successful
  // page: int 0-4095
  // offset: int 0-255
  // byte: uint8_t or byte type data
  if(flash.writeByte(page, offset, testByte)) { 
    SerialMonitor.println("Write successful!");
  }
  else {
    SerialMonitor.println("Write failed!");
  }
  SerialMonitor.println("Using readByte...");
  char printBuffer[50]; // for formatting the random values, using sprintf
  sprintf(printBuffer, "The byte on page %d at position %d is: ", page, offset);
  SerialMonitor.print(printBuffer);
  // readByte(page, offset)
  SerialMonitor.println(flash.readByte(page, offset)); // This should read 8 on the serial monitor.

}

void loop() {
  // Code that runs repeatedly goes here.
}

